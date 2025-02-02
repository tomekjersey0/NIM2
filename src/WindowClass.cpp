#include "WindowClass.h"
#include "Ripple.h"
#include "Game.h"

WindowClass::WindowClass(std::vector<WindowClass> * _Windows, int height, int width, int _y, int _x,  void (*_content)(WindowClass * parent),  bool isSelectable, bool isShowing, bool has_border) : 
    Windows(_Windows),
    std_unit(Game::getSTD_UNIT()),
    y(_y),
    x(_x),
    has_border(has_border),
    isShowing(isShowing),
    isSelectable(isSelectable),
    content(_content),
    win(nullptr),
    BorderColor(COLOR::NORMAL),
    ContentColor(COLOR::NORMAL)
{
    cur_h = height * std_unit;
    cur_w = width * std_unit * 2;
    y = _y * std_unit;
    x = _x * std_unit * 2;

    Windows->push_back(*this);
}

WindowClass::~WindowClass() {
    for (Ripple * rip : Ripples) {
        delete rip;
    }
}

std::vector<Ripple*> WindowClass::getRipples() {
    return Ripples;
}

void WindowClass::setBorderColor(COLOR color) {
    BorderColor = color;
}

void WindowClass::AddRipple(Ripple* rip) {
    Ripples.push_back(rip);
}

WINDOW * WindowClass::getWindow() {
    return win;
}

void WindowClass::InitWindow() {
    if (win == nullptr) {
        win = newwin(cur_h, cur_w, y, x); 

        // running content in here instead of in the constructor so that that the callback can use fully updated values
        // possible dynamic content positioning and rendering
        if (content) {
            content(this); // Function that adds all the objects to the be display to the window on initialization
        }
    }
    else {
        win = newwin(cur_h, cur_w, y, x);
        //std::cerr << "Window has already been initialized" << std::endl;
        if (content) {
            content(this); // Function that adds all the objects to the be display to the window on initialization
        }
    }
}

void WindowClass::Normalize(int x_offset, int y_offset) {
    x -= x_offset;
    y -= y_offset;
}

void WindowClass::setSize(int height, int width) {
    cur_h = height;
    cur_w = width;
    wresize(win, cur_h, cur_w);
}

void WindowClass::setPos(int _x, int _y) {
    if (mvwin(win, _y, _x) != ERR) {
        x = _x;
        y = _y;
    }
}

int WindowClass::getHeight() {
    return cur_h;
}        

int WindowClass::getRippleCount() {
    return Ripples.size();
}

int WindowClass::getWidth() {
    return cur_w;
}

int WindowClass::getX() {
    return x;
}

int WindowClass::getY() {
    return y;
}

bool WindowClass::IsShowing() {
    return isShowing;
}

void WindowClass::IsShowing(bool set) {
    isShowing = set;
}

bool WindowClass::IsSelectable() {
    return isSelectable;
}

void WindowClass::IsSelectable (bool set) {
    isSelectable = set;
}

void WindowClass::Update() {
    if (isShowing) {
        if (has_border) {
            wattron(win, COLOR_PAIR(BorderColor));
            box(win, 0, 0); // Draw border if needed
            wattroff(win, COLOR_PAIR(BorderColor));
        }
        for (auto rip : Ripples) {
            rip->Update();
        }
        wrefresh(win); // Refresh the window to update display
    }
}