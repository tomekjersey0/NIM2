#include <iostream>
#include <vector>

class WindowClass;

class Game
{
    private:
        static int STD_UNIT;
        static std::vector<WindowClass>* Windows;
        static std::vector<std::vector<int>>* WindowLayout;

    public:
        static int getSTD_UNIT() { return STD_UNIT; }
        static void setSTD_UNIT(int unit) { STD_UNIT = unit; }
        static void InitializeGame(std::vector<WindowClass>& windows, std::vector<std::vector<int>>& windowLayout);
        static void UpdateSTD_UNIT(int delta);
};