
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
		auto path = logger::log_directory();
		if (!path) {
			stl::report_and_fail("Failed to find standard logging directory"sv);
		}

		*path /= fmt::format("{}.log"sv, Plugin::NAME);
		auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);

		const auto level = spdlog::level::trace;

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


extern "C" DLLEXPORT constinit auto SFSEPlugin_Version = []() noexcept {
	SFSE::PluginVersionData data{};
	data.PluginVersion(1);
	data.PluginName(Plugin::NAME);
	data.AuthorName("RollingRock"sv);
	data.UsesSigScanning(true);
	data.UsesAddressLibrary(true);
	data.HasNoStructUse(true);
	data.IsLayoutDependent(true);
	data.CompatibleVersions({SFSE::RUNTIME_SF_1_7_23});

	return data;
}();

extern "C" DLLEXPORT bool SFSEAPI SFSEPlugin_Load(const SFSE::LoadInterface* a_sfse)
{
	SFSE::Init(a_sfse);

	OpenLog();
	const auto messaging = SFSE::GetMessagingInterface();
	if (!messaging || !messaging->RegisterListener(MessageHandler)) {
		return false;
	}

	logger::info("Finished loading plugin!"sv);

	return true;
}
