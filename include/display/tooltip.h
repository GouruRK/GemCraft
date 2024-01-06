#ifndef TOOLTIP_H
#define TOOLTIP_H

#define TOOLTIP_WIDTH 100

typedef struct {
    Position pos;
    Action tooltip_type;
    union {
        Tower tower;
        Gem gem;
    };
} ToolTip;

#endif
