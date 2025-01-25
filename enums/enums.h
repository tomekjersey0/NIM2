#pragma once
#ifndef ENUMS_H
#define ENUMS_H

enum MODE {
    MOVING, INTERACTING
};

enum COLOR {
    NORMAL = 1,
    SELECTED_MOVING = 2,
    SELECTED_INTERACTING = 3,
    RED = 4,
    GREEN = 5,
    BLUE = 6,
    MAGENTA = 7,
    CYAN = 8,
    YELLOW = 9
};

enum ORIENTATION {
    VERTICAL, HORIZONTAL
};

enum CONSTS {
    STD_UNIT = 10,
};

#endif