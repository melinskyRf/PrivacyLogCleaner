#include "../include/CleanupStats.h"
#include "../include/Logger.h"
#include <string>

CleanupStats::CleanupStats() {
    startTime = std::chrono::steady_clock::now();
}

void CleanupStats::AddRemoved(const std::string& category, unsigned long long size) {
    auto& stats = categories[category];
    stats.filesRemoved++;
    stats.bytesRemoved += size;
}

void CleanupStats::AddError(const std::string& category) {
    categories[category].errors++;
}

void CleanupStats::PrintSummary(Logger& logger) {
    auto endTime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);

    logger.Info("");
    logger.Info("╔══════════════════════════════════════════════════════════╗");
    logger.Info("║                 RESUMO DA LIMPEZA                        ║");
    logger.Info("╠══════════════════════════════════════════════════════════╣");

    int totalFiles = 0;
    unsigned long long totalBytes = 0;

    for (const auto& kv : categories) {
        const auto& category = kv.first;
        const auto& stats = kv.second;
        std::string sizeStr;
        if (stats.bytesRemoved < 1024) sizeStr = std::to_string(stats.bytesRemoved) + " B";
        else if (stats.bytesRemoved < 1024 * 1024) sizeStr = std::to_string(stats.bytesRemoved / 1024) + " KB";
        else sizeStr = std::to_string(stats.bytesRemoved / (1024 * 1024)) + " MB";
        char buffer[200];
        sprintf_s(buffer, "║ %-20s: %6d arquivos  %8s", category.c_str(), stats.filesRemoved, sizeStr.c_str());
        logger.Info(buffer);
        totalFiles += stats.filesRemoved;
        totalBytes += stats.bytesRemoved;
    }

    std::string totalSizeStr;
    if (totalBytes < 1024) totalSizeStr = std::to_string(totalBytes) + " B";
    else if (totalBytes < 1024 * 1024) totalSizeStr = std::to_string(totalBytes / 1024) + " KB";
    else totalSizeStr = std::to_string(totalBytes / (1024 * 1024)) + " MB";

    logger.Info("╠══════════════════════════════════════════════════════════╣");
    char buffer[200];
    sprintf_s(buffer, "║ TOTAL: %26d arquivos  %8s", totalFiles, totalSizeStr.c_str());
    logger.Info(buffer);
    logger.Info("║");
    sprintf_s(buffer, "║ Tempo total: %d segundos", (int)duration.count());
    logger.Info(buffer);
    logger.Info(std::string("║ Log salvo em: ") + logger.GetLogFilename());
    logger.Info("╚══════════════════════════════════════════════════════════╝");
}
