#pragma once

#include "SFSE/SFSE.h"
#include "RE/Starfield.h"

#include <algorithm>
#include <array>
#include <atomic>
#include <cassert>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <execution>
#include <filesystem>
#include <fstream>
#include <limits>
#include <memory>
#include <mutex>
#include <queue>
#include <span>
#include <sstream>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <variant>
#include <vector>

#pragma warning(push)
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/msvc_sink.h>
#pragma warning(pop)

namespace WinAPI
{
	using namespace SFSE::WinAPI;

	inline constexpr auto(EXCEPTION_EXECUTE_HANDLER){ static_cast<int>(1) };

	inline constexpr auto UNDNAME_NO_MS_KEYWORDS = std::uint32_t{ 0x0002 };
	inline constexpr auto UNDNAME_NO_FUNCTION_RETURNS = std::uint32_t{ 0x0004 };
	inline constexpr auto UNDNAME_NO_ALLOCATION_MODEL = std::uint32_t{ 0x0008 };
	inline constexpr auto UNDNAME_NO_ALLOCATION_LANGUAGE = std::uint32_t{ 0x0010 };
	inline constexpr auto UNDNAME_NO_THISTYPE = std::uint32_t{ 0x0060 };
	inline constexpr auto UNDNAME_NO_ACCESS_SPECIFIERS = std::uint32_t{ 0x0080 };
	inline constexpr auto UNDNAME_NO_THROW_SIGNATURES = std::uint32_t{ 0x0100 };
	inline constexpr auto UNDNAME_NO_RETURN_UDT_MODEL = std::uint32_t{ 0x0400 };
	inline constexpr auto UNDNAME_NAME_ONLY = std::uint32_t{ 0x1000 };
	inline constexpr auto UNDNAME_NO_ARGUMENTS = std::uint32_t{ 0x2000 };

	[[nodiscard]] bool IsDebuggerPresent() noexcept;

	[[nodiscard]] std::uint32_t UnDecorateSymbolName(
		const char* a_name,
		char* a_outputString,
		std::uint32_t a_maxStringLength,
		std::uint32_t a_flags) noexcept;
}

#define DLLEXPORT __declspec(dllexport)

namespace logger = SFSE::log;

namespace stl
{
	using SFSE::stl::adjust_pointer;
	using SFSE::stl::emplace_vtable;
	using SFSE::stl::enumeration;
	using SFSE::stl::report_and_fail;
	using SFSE::stl::scope_exit;
	using SFSE::stl::to_underlying;

	void asm_jump(std::uintptr_t a_from, std::size_t a_size, std::uintptr_t a_to);

	template <std::size_t N, class T>
	void write_thunk_call(std::uintptr_t a_src)
	{
		auto& trampoline = SFSE::GetTrampoline();
		T::func = trampoline.write_call<N>(a_src, T::thunk);
	}
}

using namespace std::literals;

#include "Plugin.h"
