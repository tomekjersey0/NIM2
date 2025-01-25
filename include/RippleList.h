#pragma once
#ifndef RIPPLELIST_H
#define RIPPLELIST_H

#include <iostream>
#include <vector>

#include "enums.h"

#include "RippleItem.h"
#include "WindowClass.h"
#include "Ripple.h"

class WindowClass;

class RippleList : Ripple {
    private:
        int x, y, gap;
        WindowClass * parent;
        std::vector<Ripple*> items;
        void (*content)(RippleList * parent);
        ORIENTATION orientation;

    public:
        RippleList(WindowClass * _parent, int y, int x, void (*_content)(RippleList * parent), int gap = 1, ORIENTATION orientation = ORIENTATION::VERTICAL);
        void Update() override;
        void AddRipple(Ripple * item);
        WindowClass * GetParent();
        WINDOW * GetWindow();
        void SetItemPositions();

};

#endif