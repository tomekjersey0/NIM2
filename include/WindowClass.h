#pragma once
#ifndef WINDOWCLASS_H
#define WINDOWCLASS_H

#include <curses.h>
#include <vector>
#include <iostream>
#include "enums.h"

class RipplePrint;

class WindowClass {
    private:
        bool has_border, isShowing, isSelectable;
        int cur_w, cur_h, x, y, std_unit;
        COLOR BorderColor, ContentColor;
        WINDOW *win;
        void (*content)(WindowClass * win); // Proper function pointer declaration
        std::vector<RipplePrint*> Ripples;

        std::vector<WindowClass> * Windows;

    public:
        WindowClass(std::vector<WindowClass> * _Windows, const int _std_unit, int height, int width, int _y, int _x,  void (*_content)(WindowClass * parent) = nullptr,  bool isSelectable = true, bool isShowing = true, bool has_border = true);
        ~WindowClass();
        std::vector<RipplePrint*> getRipples();
        void setBorderColor(COLOR color);
        void setContentColor(COLOR color);
        void AddRipple(RipplePrint* rip);
        WINDOW * getWindow();
        void InitWindow();
        void Normalize(int x_offset, int y_offset);
        void setSize(int height_stdunit, int width_stdunit);
        void setPos (int x_stdunit, int y_stdunit);
        int getRippleCount();
        int getHeight();       
        int getWidth();
        int getX();
        int getY();
        bool IsShowing();
        void IsShowing(bool set);
        bool IsSelectable();
        void IsSelectable (bool set) ;
        void Update();
};

#endif