#include "display/draw_mana_gauge.h"

#include <MLV/MLV_all.h>
#include <stdio.h>

#include "game_engine/player.h"
#include "utils/sector.h"
#include "display/display_const.h"

static int get_height(int max_quantity, int mana) {
    return mana * GAUGE_HEIGHT / max_quantity;
}

void draw_gauge_numbers(Player player, Sector info) {
    int text_width, text_height;
    MLV_get_size_of_text("%d", &text_width, &text_height, player.max_quantity);
    
    MLV_draw_text(info.top_left.x + info.width/2 - text_width/2,
                  info.top_left.y + text_height,
                  "%d", MLV_COLOR_WHITE, player.max_quantity);
    
    MLV_get_size_of_text("%d", &text_width, &text_height, player.mana);
    MLV_draw_text(info.top_left.x + info.width/2 - text_width/2,
                  info.bottom_right.y - text_height*2,
                  "%d", MLV_COLOR_WHITE, player.mana);
}

void draw_gauge(Player player, Sector info) {
    int height = get_height(player.max_quantity, player.mana);
    MLV_draw_filled_rectangle(info.top_left.x, info.top_left.y, info.width,
                              GAUGE_HEIGHT, MLV_COLOR_BLACK);
    MLV_draw_filled_rectangle(info.top_left.x, GAUGE_HEIGHT, info.width,
                              -height, MLV_COLOR_PURPLE1);
}
