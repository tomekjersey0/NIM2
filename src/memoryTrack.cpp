#include "memoryTrack.h"
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