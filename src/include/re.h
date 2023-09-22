// export from praydog's regenny....will replace as commonlib comes online

namespace IFPB
{
	namespace RE
	{
		class PlayerCharacter : public ::RE::Actor
		{		
		public:
			inline static PlayerCharacter* GetSingleton()
			{
				static REL::Relocation<PlayerCharacter**> singleton{ REL::Offset(0x05595BA8) };
				return *singleton;
			}  
		};


		struct Matrix4x4
		{
			float m[4][4];  // 0x0
		};                  // Size: 0x40

		struct Quaternion
		{
			float x;  // 0x0
			float y;  // 0x4
			float z;  // 0x8
			float w;  // 0xc
		};            // Size: 0x10

		struct BSString
		{
			uint64_t unk;  // 0x0
			uint32_t len;  // 0x8
		private:
			char pad_c[0xc];

		public:
			// Metadata: utf8*
			char str[56];  // 0x18
		};                 // Size: 0x50

		struct NiRefObject
		{
			void* vtable;                    // 0x0
			uint32_t ref_count;              // 0x8
			uint32_t unk_thing_nirefobject;  // 0xc
		};                                   // Size: 0x10

		struct NiObject : public NiRefObject
		{
		};  // Size: 0x10

		struct NiObjectNET : public NiObject
		{
			BSString* name;  // 0x10
		private:
			char pad_18[0x20];

		public:
		};  // Size: 0x38

		struct NiAVObject : public NiObjectNET
		{
			NiAVObject* parent;         // 0x38
			Matrix4x4 local_transform;  // 0x40
			Matrix4x4 transform;        // 0x80
			Matrix4x4 transform2;       // 0xc0
			Quaternion rotation;        // 0x100
		private:
			char pad_110[0x8];

		public:
			uint32_t flags;  // 0x118
		private:
			char pad_11c[0xc];

		public:
			int32_t frame_count;  // 0x128
		private:
			char pad_12c[0x4];

		public:
		};  // Size: 0x130

		struct NiNode : public NiAVObject
		{
			uint32_t handle;  // 0x130
		private:
			char pad_134[0x4];

		public:
			NiNode** next;                      // 0x138
			uint8_t num_children_or_allocated;  // 0x140
		private:
			char pad_141[0x1];

		public:
			uint8_t num_children;  // 0x142
		private:
			char pad_143[0xd];

		public:
		};  // Size: 0x150

		struct LOADED_REF_DATA
		{
		public:
			// members
			void* handleList;    // 00 - TODO
			NiAVObject* data3D;  // 08	};
		};

	}
}
