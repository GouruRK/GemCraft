#ifndef TOOLTIP_H
#define TOOLTIP_H

#define TOOLTIP_WIDTH 150

#include "game_engine/gem.h"
#include "game_engine/tower.h"
#include "utils/position.h"
#include "display/game_sectors.h"

typedef enum {
    GEM_TYPE,
    TOWER_TYPE
} ToolTipType;

typedef struct {
    Position pos;
    ToolTipType type;
    union {
        Tower tower;
        Gem gem;
    };
} ToolTip;

ToolTip init_gem_tooltip(Gem gem, Position pos);

ToolTip init_tower_tooltip(Tower tower, Position pos);

void display_tool_tip(const GameSectors* sectors, ToolTip tip);

#endif
