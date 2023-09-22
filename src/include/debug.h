#include "include/re.h"


int fc = 0;

namespace IFPB
{
	namespace Debug
	{

		namespace detail
		{
			void toggleVis(RE::NiNode* nde, bool hide, bool updateSelf)
			{
				try {
					if (nde->num_children == 0 || nde->num_children_or_allocated == 0 || nde->next == nullptr) {
						return;
					}

					if (updateSelf) {
						if (hide) {
							nde->flags |= 0x1;
						} else {
							nde->flags &= 0xfffffffffffffffe;
						}
					}

					for (auto i = 0; i < std::min<uint8_t>(nde->num_children, nde->num_children_or_allocated); ++i) {
						if (nde->next == nullptr) {
							continue;
						}
						auto nextNode = nde->next[i];
						if (nextNode) {
							toggleVis(nextNode, hide, true);
						}
					}
				} catch (...) {
				}
			}

			void printChildren(RE::NiNode* child, std::string padding)
			{
				try {
					padding += "....";
					logger::info("{} -> {}{} : children = {}", fc, padding.c_str(), child->name->str, child->num_children_or_allocated);

					if (child->num_children == 0 || child->num_children_or_allocated == 0 || child->next == nullptr) {
						return;
					}

					for (auto i = 0; i < std::min<uint8_t>(child->num_children, child->num_children_or_allocated); ++i) {
						auto nextNode = child->next[i];
						if (nextNode) {
							printChildren(nextNode, padding);
						}
					}
				} catch (...) {
				}
			}

			void printNodes(RE::NiNode* nde)
			{
				// print root node info first
				logger::info("{} -> {} : children = {}", fc, nde->name->str, nde->num_children_or_allocated);

				std::string padding = "";
				try {
					if (nde->num_children == 0 || nde->num_children_or_allocated == 0 || nde->next == nullptr) {
						return;
					}

					for (auto i = 0; i < std::min<uint8_t>(nde->num_children, nde->num_children_or_allocated); ++i) {
						auto nextNode = nde->next[i];
						if (nextNode) {
							printChildren(nextNode, padding);
						}
					}
				} catch (...) {
				}
			}
		}

		struct Hook
		{
			static void Thunk(uint64_t rcx)
			{
				RE::LOADED_REF_DATA* data = nullptr;
				RE::PlayerCharacter* player = RE::PlayerCharacter::GetSingleton();
				if (player) {
					data = static_cast<RE::LOADED_REF_DATA*>(player->loadedData);
					if (data != nullptr) {
						//		logger::info("frame = {}", fc);
						//	fc++;

						detail::toggleVis((RE::NiNode*)data->data3D, false, true);
						//auto node = data->data3D;
						//while (node->parent) {
						//	node = node->parent;
						//}
						//node = node->parent;

						//detail::printNodes((RE::NiNode*)node);
					}
				}
				func(rcx);

				return;
			}
			static inline REL::Relocation<decltype(Thunk)> func;
			static inline std::uintptr_t address{ REL::Relocation<std::uintptr_t>(REL::Offset(0x23fafb4)).address() };
		};

		void Install()
		{
			SFSE::stl::write_thunk_call<Hook>();
		}
	}
}
