#pragma once
#include <set>
#include <string>
#include <vector>

class Config {
public:
    static Config* GetInstance();

    bool verbose = true;
    int maxRecursionDepth = 3;
    unsigned long long maxFileSize = 50ULL * 1024 * 1024; // 50MB
    bool dryRun = false;

    std::set<std::string> allowedExtensions;
    std::set<std::string> blockedExtensions;
    std::vector<std::string> protectedPaths;
    std::set<std::string> appExecutionKeywords;
    std::set<std::string> recentFileKeywords;
    std::set<std::string> usbKeywords;
    std::set<std::string> deviceEventKeywords;
    std::set<std::string> downloadKeywords;

private:
    Config();
    void LoadDefaultConfig();
    static Config* instance;
};
