/**
 * @file tooltip.h
 * @author Coserariu Alain & Kies Remy
 * @brief Display tooltip of the given object
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef TOOLTIP_H
#define TOOLTIP_H

#define TOOLTIP_WIDTH 150

#include "game_engine/gem.h"
#include "game_engine/tower.h"
#include "utils/position.h"
#include "utils/sector.h"

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

/**
 * @brief Creates a tooltip at `pos` for given gem
 * 
 * @param gem gem information
 * @param pos onscreen gem position
 * @return
 */
ToolTip init_gem_tooltip(Gem gem, Position pos);

/**
 * @brief Creates a tooltip at `pos` for given tower
 * 
 * @param tower tower information
 * @param pos onscreen tower position
 * @return
 */
ToolTip init_tower_tooltip(Tower tower, Position pos);

/**
 * @brief Display selected tooltip
 * 
 * @param window window sector to change coordinates if tooltip is out of frame
 * @param tip tooltip to display
 */
void display_tool_tip(Sector window, ToolTip tip);

#endif
