#include "display/tooltip.h"

#include <MLV/MLV_all.h>

#include "game_engine/gem.h"
#include "game_engine/tower.h"
#include "display/game_sectors.h"
#include "display/color.h"
#include "utils/position.h"

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

static void reposition(const GameSectors* sectors, Position* pos, int height) {
    if (pos->x + TOOLTIP_WIDTH > sectors->window.width) {
        pos->x -= TOOLTIP_WIDTH;
    }
    if (pos->y + height > sectors->window.height) {
        pos->y -= height;
    }
}

static void display_gem_tool_tip(const GameSectors* sectors, Position pos, Gem gem) {
    int height = 40;
    reposition(sectors, &pos, height);

    // outline
    MLV_draw_filled_rectangle(pos.x, pos.y, TOOLTIP_WIDTH, height, MLV_rgba(51, 51, 51, 255));
    
    // Gem type
    pos.x += 5; // apply margin
    int w, h;
    MLV_get_size_of_text("Gem of type ", &w, &h);
    MLV_draw_text(pos.x, pos.y, "Gem of type ", MLV_COLOR_WHITE);
    MLV_draw_text(pos.x + w, pos.y, "%s", transform_color(gem.color), gem_name_array[gem.type]);

    // Gem level
    MLV_draw_text(pos.x, pos.y + h + 5, "Level : %d", MLV_COLOR_WHITE, gem.level);
}

static void display_tower_tool_tip(const GameSectors* sectors, Position pos, Tower tower) {
    int height = 20;
    if (tower.hold_gem) {
        height = 50;
    }
    reposition(sectors, &pos, height);

    // outline
    MLV_draw_filled_rectangle(pos.x, pos.y, TOOLTIP_WIDTH, height, MLV_rgba(51, 51, 51, 255));

    // Tower
    pos.x += 5; // apply margin
    int w, h;
    MLV_get_size_of_text("Radius %d", &w, &h, 5);
    MLV_draw_text(pos.x, pos.y, "Radius %d", MLV_COLOR_WHITE, 5);

    if (tower.hold_gem) {
    // gem type
    MLV_get_size_of_text("Gem of type ", &w, &h);
    MLV_draw_text(pos.x, pos.y + 15, "Gem of type ", MLV_COLOR_WHITE);
    MLV_draw_text(pos.x + w, pos.y + 15, "%s", transform_color(tower.gem.color), gem_name_array[tower.gem.type]);

    // gem level
    MLV_draw_text(pos.x, pos.y + h + 15, "Level : %d", MLV_COLOR_WHITE, tower.gem.level);
    }
}

void display_tool_tip(const GameSectors* sectors, ToolTip tip) {
    if (tip.type == GEM_TYPE) {
        display_gem_tool_tip(sectors, tip.pos, tip.gem);
    } else {
        display_tower_tool_tip(sectors, tip.pos, tip.tower);
    }
}

