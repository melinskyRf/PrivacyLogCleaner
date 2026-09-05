#pragma once
#include <map>
#include <string>
#include <chrono>

class Logger;

class CleanupStats {
private:
    struct CategoryStats {
        int filesRemoved = 0;
        unsigned long long bytesRemoved = 0;
        int errors = 0;
    };
    std::map<std::string, CategoryStats> categories;
    std::chrono::steady_clock::time_point startTime;

public:
    CleanupStats();
    void AddRemoved(const std::string& category, unsigned long long size);
    void AddError(const std::string& category);
    void PrintSummary(Logger& logger);
};
