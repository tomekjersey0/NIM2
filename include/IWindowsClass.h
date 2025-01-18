#pragma once

#include <vector>
#include <curses.h> // For WINDOW
#include "RipplePrint.h" // For RipplePrint
#include "enums.h" // For COLOR

class IWindowClass {
public:
    virtual ~IWindowClass() = default;
    virtual void setBorderColor(COLOR color) = 0;
    virtual void AddRipple(RipplePrint* rip) = 0;
    virtual WINDOW* getWindow() = 0;
    virtual void InitWindow() = 0;
    virtual void Normalize(int x_offset, int y_offset) = 0;
    virtual void setSize(int height_stdunit, int width_stdunit) = 0;
    virtual void setPos(int x_stdunit, int y_stdunit) = 0;
    virtual int getRippleCount() = 0;
    virtual int getHeight() = 0;
    virtual int getWidth() = 0;
    virtual int getX() = 0;
    virtual int getY() = 0;
    virtual bool IsShowing() = 0;
    virtual void IsShowing(bool set) = 0;
    virtual bool IsSelectable() = 0;
    virtual void IsSelectable(bool set) = 0;
    virtual void Update() = 0;
};