#pragma once
#include <string>
#include <chrono>

class IRipplePrint {
    public:
        virtual ~IRipplePrint() = default;
        virtual std::chrono::_V2::system_clock::time_point getStartTime() = 0;
        virtual int getX() = 0;
        virtual int getY() = 0;
        virtual std::string getText() = 0;
        virtual void Update() = 0;
};