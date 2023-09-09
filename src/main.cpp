
namespace
{


	void SFSEAPI MessageHandler(SFSE::MessagingInterface::Message* a_message)
	{
		switch (a_message->type) {
		case SFSE::MessagingInterface::kPostPostLoad:
			{
			}
			break;
		}
	}

	void OpenLog()
	{
#ifndef NDEBUG
		auto sink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
#else
		auto path = logger::log_directory();
		if (!path) {
			stl::report_and_fail("Failed to find standard logging directory"sv);
		}

		*path /= fmt::format("{}.log"sv, Plugin::NAME);
		auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);
#endif

#ifndef NDEBUG
		const auto level = spdlog::level::trace;
#else
		const auto level = spdlog::level::trace;
#endif

		auto log = std::make_shared<spdlog::logger>("global log"s, std::move(sink));
		log->set_level(level);
		log->flush_on(level);

		spdlog::set_default_logger(std::move(log));
		spdlog::set_pattern("[%Y-%m-%d %H-%M-%S.%e][%-16s:%-4#][%=7l]: %v"s);

		logger::info(
			"{} v{}.{}.{}"sv,
			Plugin::NAME,
			Plugin::VERSION[0],
			Plugin::VERSION[1],
			Plugin::VERSION[2]);
	}

}


extern "C" DLLEXPORT bool SFSEAPI SFSEPlugin_Query(const SFSE::QueryInterface* a_sfse, SFSE::PluginInfo* a_info)
{
	a_info->infoVersion = SFSE::PluginInfo::kVersion;
	a_info->name = Plugin::NAME.data();
	a_info->version = Plugin::VERSION[0];

	OpenLog();
	//if (a_sfse->IsEditor()) {
	//	logger::critical("loaded in editor"sv);
	//	return false;
	//}

	const auto ver = a_sfse->RuntimeVersion();
	if (ver < SFSE::RUNTIME_LATEST) {
		logger::critical("unsupported runtime v{}"sv, ver.string());
		return false;
	}

	return true;
}

extern "C" DLLEXPORT bool SFSEAPI SFSEPlugin_Load(const SFSE::LoadInterface* a_sfse)
{
	SFSE::Init(a_sfse);

	const auto messaging = SFSE::GetMessagingInterface();
	if (!messaging || !messaging->RegisterListener(MessageHandler)) {
		return false;
	}

	return true;
}
