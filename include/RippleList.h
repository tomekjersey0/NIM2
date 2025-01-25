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
        WindowClass * parent;
        std::vector<Ripple*> items;
        void (*content)(RippleList * parent);

    public:
        RippleList(WindowClass * _parent, int x, int y, void (*_content)(RippleList * parent), ORIENTATION orientation = ORIENTATION::VERTICAL);
        void Update() override;
        void AddRipple(Ripple * item) { items.push_back(item); };
};

#endif