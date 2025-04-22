#include "memoryTrack.h"
#ifdef _WIN32
#include <windows.h>
#include <psapi.h>

long getMemoryUsageKB() {
    PROCESS_MEMORY_COUNTERS_EX pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc))) {
        return static_cast<long>(pmc.WorkingSetSize / 1024);
    }
    return -1;
}
#else
#include <fstream>
#include <sstream>
#include <string>

long getMemoryUsageKB() {
    std::ifstream statStream("/proc/self/status", std::ios_base::in);
    std::string line;
    while (std::getline(statStream, line)) {
        if (line.substr(0, 6) == "VmRSS:") {
            std::istringstream iss(line);
            std::string key;
            long value;
            std::string unit;
            iss >> key >> value >> unit;
            return value;
        }
    }
    return -1;
}
#endif