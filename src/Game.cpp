#include "Game.h"
#include "WindowClass.h"

int Game::STD_UNIT = 10;
std::vector<WindowClass>* Game::Windows = nullptr;
std::vector<std::vector<int>>* Game::WindowLayout = nullptr;

void Game::InitializeGame(std::vector<WindowClass>& windows, std::vector<std::vector<int>>& windowLayout) {
    Windows = &windows;
    WindowLayout = &windowLayout;
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