#include "../include/Logger.h"
#include <windows.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>

namespace fs = std::filesystem;

struct Logger::Impl {
    std::wofstream logFile;
    std::string logFilename;
    bool consoleOutput;
    std::mutex logMutex;
    HANDLE hConsole;

    Impl(bool console)
        : consoleOutput(console) {
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        logFilename.clear();
    }

    std::string GetTimestamp() {
        using namespace std::chrono;
        auto now = system_clock::now();
        auto time = system_clock::to_time_t(now);
        std::tm tm;
        localtime_s(&tm, &time);
        char buffer[100];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm);
        return std::string(buffer);
    }

    void WriteToConsole(const std::string& message, WORD color) {
        if (!consoleOutput) return;
        SetConsoleTextAttribute(hConsole, color);
        std::cout << message << std::endl;
        SetConsoleTextAttribute(hConsole, 7);
    }
};

Logger::Logger(bool console) : pimpl(new Impl(console)) {}
Logger::~Logger() { delete pimpl; }

void Logger::Info(const std::string& message) {
    std::lock_guard<std::mutex> lock(pimpl->logMutex);
    std::string logMessage = "[INFO] " + pimpl->GetTimestamp() + " - " + message;
    pimpl->WriteToConsole(logMessage, 7);
}
void Logger::Success(const std::string& message) {
    std::lock_guard<std::mutex> lock(pimpl->logMutex);
    std::string logMessage = "[OK] " + pimpl->GetTimestamp() + " - " + message;
    pimpl->WriteToConsole(logMessage, 10);
}
void Logger::Warning(const std::string& message) {
    std::lock_guard<std::mutex> lock(pimpl->logMutex);
    std::string logMessage = "[WARN] " + pimpl->GetTimestamp() + " - " + message;
    pimpl->WriteToConsole(logMessage, 14);
}
void Logger::Error(const std::string& message) {
    std::lock_guard<std::mutex> lock(pimpl->logMutex);
    std::string logMessage = "[ERROR] " + pimpl->GetTimestamp() + " - " + message;
    pimpl->WriteToConsole(logMessage, 12);
}

void Logger::FileRemoved(const fs::path& filePath, uintmax_t size) {
    std::lock_guard<std::mutex> lock(pimpl->logMutex);
    std::string sizeStr;
    if (size < 1024) sizeStr = std::to_string(size) + " B";
    else if (size < 1024 * 1024) sizeStr = std::to_string(size / 1024) + " KB";
    else sizeStr = std::to_string(size / (1024 * 1024)) + " MB";
    std::string logMessage = "[REMOVED] " + pimpl->GetTimestamp() + " - " + filePath.string() + " (" + sizeStr + ")";
    pimpl->WriteToConsole(logMessage, 10);
}

void Logger::FileFailed(const fs::path& filePath, const std::string& reason) {
    std::lock_guard<std::mutex> lock(pimpl->logMutex);
    std::string logMessage = "[FAILED] " + pimpl->GetTimestamp() + " - " + filePath.string() + " - " + reason;
    pimpl->WriteToConsole(logMessage, 12);
}

std::string Logger::GetLogFilename() const { return pimpl->logFilename; }
