#include "display/draw_mana_gauge.h"

#include <MLV/MLV_all.h>
#include <stdio.h>

#include "game_engine/player.h"
#include "utils/sector.h"
#include "display/display_const.h"

static int get_height(int max_quantity, int mana) {
    return mana * GAUGE_HEIGHT / max_quantity;
}

void draw_gauge(Player player, Sector info) {
    int height = get_height(player.max_quantity, player.mana);
    MLV_draw_filled_rectangle(info.top_left.x, info.top_left.y, info.width, GAUGE_HEIGHT, MLV_COLOR_BLACK);
    MLV_draw_filled_rectangle(info.top_left.x, GAUGE_HEIGHT, info.width, -height, MLV_COLOR_PURPLE1);
}
