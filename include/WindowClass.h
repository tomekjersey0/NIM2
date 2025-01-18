#pragma once
#ifndef WINDOWCLASS_H
#define WINDOWCLASS_H

#include <curses.h>
#include <vector>
#include <iostream>
#include "enums.h"
#include <RipplePrint.h>

class WindowClass {
    private:
        bool has_border, isShowing, isSelectable;
        int cur_w, cur_h, x, y, std_unit;
        COLOR BorderColor;
        WINDOW *win;
        void (*content)(WindowClass * win); // Proper function pointer declaration
        std::vector<RipplePrint*> Ripples;

        std::vector<WindowClass> * Windows;

    public:
        WindowClass(std::vector<WindowClass> * _Windows, const int _std_unit, int height, int width, int _y, int _x,  void (*_content)(WindowClass * parent) = nullptr,  bool isSelectable = true, bool isShowing = true, bool has_border = true) : 
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

        ~WindowClass() {
            for (RipplePrint * rip : Ripples) {
                delete rip;
            }
        }

        std::vector<RipplePrint*> getRipples();

        void setBorderColor(COLOR color);
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