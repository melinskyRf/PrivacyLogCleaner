#include "../include/Config.h"

Config* Config::instance = nullptr;

Config* Config::GetInstance() {
    if (instance == nullptr) {
        instance = new Config();
    }
    return instance;
}

Config::Config() {
    LoadDefaultConfig();
}

void Config::LoadDefaultConfig() {
    // Extensões seguras para remover
    allowedExtensions = {
        ".log", ".tmp", ".crdownload", ".part", ".lnk", ".url",
        ".sqlite", ".dat", ".etl", ".blf", ".regtrans-ms",
        ".evtx", ".etl", ".wpv", ".txt", ".csv", ".json",
        ".cache", ".bak", ".old", ".temp", ".dmp", ".mdmp"
    };

    // Extensões que NUNCA devem ser removidas
    blockedExtensions = {
        ".exe", ".dll", ".sys", ".drv", ".ini", ".inf", ".cat",
        ".msi", ".msp", ".ocx", ".cpl", ".scr", ".com", ".bat",
        ".cmd", ".ps1", ".vbs", ".js", ".jar", ".class", ".bin",
        ".mui", ".man", ".mof", ".nls", ".pol", ".ppd", ".rom"
    };

    // Paths protegidos
    protectedPaths = {
        "C:\\Windows\\System32",
        "C:\\Windows\\SysWOW64",
        "C:\\Program Files",
        "C:\\Program Files (x86)",
        "C:\\Windows\\WinSxS",
        "C:\\Windows\\assembly",
        "C:\\Windows\\Microsoft.NET",
        "C:\\Windows\\Installer",
        "C:\\Windows\\Servicing",
        "C:\\Windows\\Logs\\CBS",
        "C:\\Windows\\Logs\\DISM",
        "C:\\Windows\\Debug",
        "C:\\Windows\\System32\\config",
        "C:\\Windows\\System32\\drivers",
        "C:\\Windows\\System32\\DriverStore",
        "C:\\Windows\\System32\\Tasks",
        "C:\\Windows\\System32\\wbem"
    };

    appExecutionKeywords = {
        "execution", "executed", "launch", "started", "closed",
        "opened", "runtime", "application", "app", "program",
        "exe", "process", "task", "background", "foreground",
        "active", "focus", "window", "instance", "pid",
        "session", "logged", "userinit", "shell", "explorer",
        "startmenu", "taskbar", "desktop", "shortcut"
    };

    recentFileKeywords = {
        "recent", "recently", "opened", "accessed", "viewed",
        "edited", "modified", "saved", "downloaded", "uploaded",
        "quickaccess", "frequent", "popular", "favorite",
        "history", "timeline", "activity", "usage"
    };

    usbKeywords = {
        "usb", "drive", "removable", "external", "mass storage",
        "flash", "pendrive", "thumbdrive", "memory card",
        "sd card", "mmc", "scsi", "disk", "volume",
        "mount", "unmount", "eject", "connect", "disconnect"
    };

    deviceEventKeywords = {
        "entrada", "saida", "entrada e saida", "conexao", "conexão", "desconexao", "desconexão",
        "connect", "disconnect", "mount", "unmount", "eject", "ejetado", "expulso", "expulsao",
        "arrival", "removal", "removed", "inserted", "unplugged", "plugged",
        "moviment", "movimento", "movement", "moved", "removed"
    };

    downloadKeywords = {
        "download", "downloaded", "downloading", "transfer",
        "browser", "chrome", "edge", "firefox", "opera",
        "brave", "vivaldi", "torrent", "p2p", "http",
        "ftp", "webclient", "urlcache", "iedownload"
    };
}
