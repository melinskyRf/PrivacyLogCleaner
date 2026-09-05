#include "../include/Config.h"
#include "../include/Logger.h"
#include "../include/CleanupStats.h"
#include "../include/SecurityChecker.h"
#include "../include/Modules.h"

// Include implementations to build as single translation unit
#include "../src/Config.cpp"
#include "../src/Logger.cpp"
#include "../src/CleanupStats.cpp"
#include "../src/SecurityChecker.cpp"
#include "../src/CleanupModule.cpp"
#include "../src/Modules.cpp"

#include <windows.h>
#include <vector>
#include <memory>

#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "userenv.lib")
#pragma comment(lib, "setupapi.lib")
#pragma comment(lib, "Cfgmgr32.lib")

int main() {
    Config* cfg = Config::GetInstance();
    Logger logger(true);
    CleanupStats stats;
    SecurityChecker security;

    // Parse args
    int argc = __argc;
    wchar_t** argv = __wargv;
    for (int i = 1; i < argc; ++i) {
        std::wstring a = argv[i];
        std::string arg;
        int size = WideCharToMultiByte(CP_UTF8, 0, a.c_str(), -1, NULL, 0, NULL, NULL);
        arg.resize(size);
        WideCharToMultiByte(CP_UTF8, 0, a.c_str(), -1, &arg[0], size, NULL, NULL);
        if (!arg.empty() && arg.back() == '\0') arg.pop_back();
        if (arg == "--dry-run" || arg == "-n") cfg->dryRun = true;
    }

    // Prepare modules
    std::vector<std::unique_ptr<CleanupModule>> modules;
    modules.push_back(std::make_unique<AppExecutionModule>(&logger, &stats, &security));
    modules.push_back(std::make_unique<RecentFilesModule>(&logger, &stats, &security));
    modules.push_back(std::make_unique<USBLogsModule>(&logger, &stats, &security));
    modules.push_back(std::make_unique<DownloadLogsModule>(&logger, &stats, &security));
    modules.push_back(std::make_unique<CommandHistoryModule>(&logger, &stats, &security));
    modules.push_back(std::make_unique<ForensicReportModule>(&logger, &stats, &security));

    logger.Info("");
    if (cfg->dryRun) logger.Info("▶ MODO DRY-RUN: mostrando o que seria apagado (nenhuma remoção será feita)");
    else logger.Info("▶ INICIANDO LIMPEZA REAL...");

    for (const auto& m : modules) m->Execute();

    stats.PrintSummary(logger);

    return 0;
}