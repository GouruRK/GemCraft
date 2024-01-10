#include "display/tooltip.h"

#include <MLV/MLV_all.h>

#include "game_engine/gem.h"
#include "game_engine/tower.h"
#include "display/color.h"
#include "utils/position.h"
#include "utils/sector.h"
#include "display/display_const.h"

char* gem_name_array[] = {
    [PYRO] = "Pyro",
    [DENDRO] = "Dendro",
    [HYDRO] = "Hydro",
    [MIXTE] = "Mixte"
};

ToolTip init_gem_tooltip(Gem gem, Position pos) {
    ToolTip tip;
    tip.type = GEM_TYPE;
    tip.gem = gem;
    tip.pos = pos;
    return tip;
}

ToolTip init_tower_tooltip(Tower tower, Position pos) {
    ToolTip tip;
    tip.type = TOWER_TYPE;
    tip.tower = tower;
    tip.pos = pos;
    return tip;
}

/**
 * @brief Change pos's coordinates for the tooltip if its current display
 *        is offscreen
 * 
 * @param window 
 * @param pos 
 * @param height 
 */

static void reposition(Sector window, Position* pos, int height) {
    if (pos->x + TOOLTIP_WIDTH > window.width) {
        pos->x -= TOOLTIP_WIDTH;
    }
    if (pos->y + height > window.height) {
        pos->y -= height;
    }
}

/**
 * @brief Display gem information at a given position with an 
 *        ordinate offset `y`
 * 
 * @param pos 
 * @param gem 
 * @param y 
 */
static void display_gem_information(Position pos, Gem gem, int y) {
    int w, h;
    MLV_get_size_of_text("Gem of type ", &w, &h);
    MLV_draw_text(pos.x, pos.y + y, "Gem of type ", MLV_COLOR_WHITE);
    MLV_draw_text(pos.x + w, pos.y + y, "%s", transform_color(gem.color),
                  gem_name_array[gem.type]);

    // Gem level
    MLV_draw_text(pos.x, pos.y + h + y, "Level : %d", MLV_COLOR_WHITE,
                  gem.level);
}

/**
 * @brief Display given gem tooltip at pos
 * 
 * @param window 
 * @param pos 
 * @param gem 
 */
static void display_gem_tool_tip(Sector window, Position pos, Gem gem) {
    int height = 40;
    reposition(window, &pos, height);

    // outline
    MLV_draw_filled_rectangle(pos.x, pos.y, TOOLTIP_WIDTH, height,
                              MLV_rgba(51, 51, 51, 255));
    
    // Gem type
    pos.x += 5; // apply margin
    display_gem_information(pos, gem, 0);
}


/**
 * @brief Display tower tooltip
 * 
 * @param window 
 * @param pos 
 * @param tower 
 */
static void display_tower_tool_tip(Sector window, Position pos, Tower tower) {
    int height = 20;
    if (tower.hold_gem) {
        height = 50;
    }
    reposition(window, &pos, height);

    // outline
    MLV_draw_filled_rectangle(pos.x, pos.y, TOOLTIP_WIDTH, height,
                              MLV_rgba(51, 51, 51, 255));

    // Tower
    pos.x += 5; // apply margin
    int w, h;
    Position center_tower = cell_center(tower.pos);
    center_tower.x *= CELL_SIZE;
    center_tower.y *= CELL_SIZE;
    if (tower.hold_gem) {
        float radius = calc_radius_shoot_range(&tower.gem);
        MLV_get_size_of_text("Radius %.1f", &w, &h, radius);
        MLV_draw_circle(center_tower.x, center_tower.y, 
                        radius * CELL_SIZE, MLV_COLOR_BROWN);
        MLV_draw_text(pos.x, pos.y, "Radius %.1f", MLV_COLOR_WHITE, radius);
    } else {
        MLV_get_size_of_text("Radius %d", &w, &h, 0);
        MLV_draw_text(pos.x, pos.y, "Radius %d", MLV_COLOR_WHITE, 0);
    }

    if (tower.hold_gem) {
        display_gem_information(pos, tower.gem, h + 5);
    }
}

void display_tool_tip(Sector window, ToolTip tip) {
    if (tip.type == GEM_TYPE) {
        display_gem_tool_tip(window, tip.pos, tip.gem);
    } else {
        display_tower_tool_tip(window, tip.pos, tip.tower);
    }
}
