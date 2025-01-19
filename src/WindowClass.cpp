#include "RipplePrint.h"
#include "WindowClass.h"

WindowClass::WindowClass(std::vector<WindowClass> * _Windows, const int _std_unit, int height, int width, int _y, int _x,  void (*_content)(WindowClass * parent),  bool isSelectable, bool isShowing, bool has_border) : 
    Windows(_Windows),
    std_unit(_std_unit),
    y(_y),
    x(_x),
    has_border(has_border),
    isShowing(isShowing),
    isSelectable(isSelectable),
    content(_content) // Direct initialization
{
    win = nullptr;
    cur_h = height * std_unit;
    cur_w = width * std_unit * 2;
    y = _y * std_unit;
    x = _x * std_unit * 2;

    Windows->push_back(*this);
}

WindowClass::~WindowClass() {
    for (RipplePrint * rip : Ripples) {
        delete rip;
    }
}

std::vector<RipplePrint*> WindowClass::getRipples() {
    return Ripples;
}

void WindowClass::setBorderColor(COLOR color) {
    BorderColor = color;
}

void WindowClass::AddRipple(RipplePrint* rip) {
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
        std::cerr << "Window has already been initialized" << std::endl;
    }
}

void WindowClass::Normalize(int x_offset, int y_offset) {
    x -= x_offset;
    y -= y_offset;
}

void WindowClass::setSize(int height_stdunit, int width_stdunit) {
    cur_h = height_stdunit * std_unit;
    cur_w = width_stdunit * std_unit;
    resize_window(win, cur_h, cur_w);
}

void WindowClass::setPos (int x_stdunit, int y_stdunit) {
    int _x = x_stdunit * std_unit;
    int _y = y_stdunit * std_unit;
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