#include "Game.h"
#include "WindowClass.h"
#ifdef _WIN32
    #include <windows.h>
#else
    #include <sys/ioctl.h>
#endif
#include <unistd.h>

int Game::STD_UNIT = 10;
int Game::TERMINAL_WIDTH = 0;
int Game::TERMINAL_HEIGHT = 0;
std::vector<WindowClass>* Game::Windows = nullptr;
std::vector<std::vector<int>>* Game::WindowLayout = nullptr;

void Game::getPhysicalTerminalSize(int & rows, int &cols) {
    #ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    #else
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        rows = w.ws_row;
        cols = w.ws_col;
    #endif
}

void Game::InitializeGame(std::vector<WindowClass>& windows, std::vector<std::vector<int>>& windowLayout) {
    Windows = &windows;
    WindowLayout = &windowLayout;
    Game::getPhysicalTerminalSize(TERMINAL_HEIGHT, TERMINAL_WIDTH);
}

void Game::UpdateSTD_UNIT(int delta) {
    if (STD_UNIT + delta < 1)
        return;
    STD_UNIT += delta;
    
    resize_term(1000,1000);
    for (auto& window : *Windows) {
        int oldHeight = window.getHeight();
        int oldWidth = window.getWidth();
        int oldSTD_UNIT = STD_UNIT - delta;

        int oldX = window.getX();
        int oldY = window.getY();

        window.setSize(oldHeight / oldSTD_UNIT * STD_UNIT, oldWidth / oldSTD_UNIT * STD_UNIT);
        window.setPos(oldX / oldSTD_UNIT * STD_UNIT, oldY / oldSTD_UNIT * STD_UNIT);
    }
}