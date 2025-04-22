#pragma once
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>

class WindowClass;

class Game
{
    private:
        static int STD_UNIT;
        static int TERMINAL_WIDTH;
        static int TERMINAL_HEIGHT;
        static std::vector<WindowClass>* Windows;
        static std::vector<std::vector<int>>* WindowLayout;

    public:
        static int getSTD_UNIT() { return STD_UNIT; }
        static int getTERMINAL_WIDTH() { return TERMINAL_WIDTH; }
        static int getTERMINAL_HEIGHT() { return TERMINAL_HEIGHT; }
        static void setSTD_UNIT(int unit) { STD_UNIT = unit; }
        static void InitializeGame(std::vector<WindowClass>& windows, std::vector<std::vector<int>>& windowLayout);
        static void UpdateSTD_UNIT(int delta);
        static void getPhysicalTerminalSize(int& rows, int& cols);
        static void resetStoredTerminalSize() {getPhysicalTerminalSize(TERMINAL_HEIGHT, TERMINAL_WIDTH);}
};

#endif