#pragma once
#include <string>
#include <filesystem>
#include <mutex>

namespace fs = std::filesystem;

class Logger {
public:
    Logger(bool console = true);
    ~Logger();

    void Info(const std::string& message);
    void Success(const std::string& message);
    void Warning(const std::string& message);
    void Error(const std::string& message);

    void FileRemoved(const fs::path& filePath, uintmax_t size);
    void FileFailed(const fs::path& filePath, const std::string& reason);

    std::string GetLogFilename() const;

private:
    struct Impl;
    Impl* pimpl;
};
