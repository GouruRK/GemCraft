#include "display/draw_button.h"

#include <MLV/MLV_all.h>

#include "display/draw_mana_gauge.h"
#include "display/game_sectors.h"
#include "game_engine/game.h"
#include "utils/sector.h"
#include "display/display_const.h"

// TODO : save somehow computation of position depending the text
// because a text position for a button is always the same
// and don't need to be re-computed each time the function is called

/**
 * @brief Draw a button in the given sector with text as its label
 *
 * @param button
 * @param text
 */
static void draw_button(Sector button, char* text) {
    int text_width, text_height;
    int x, y;

    MLV_Color color = BUTTON_BACKGROUND_COLOR;
    MLV_get_mouse_position(&x, &y);
    if (is_coord_in_sector(button, x, y)) {
        color = BUTTON_HOVER_COLOR;
    }

    MLV_get_size_of_text(text, &text_width, &text_height);
    x = button.top_left.x + button.width / 2 - text_width / 2;
    y = button.top_left.y + button.height / 2 - text_height / 2;

    MLV_draw_filled_rectangle(button.top_left.x, button.top_left.y,
                              button.width, button.height, color);

    MLV_draw_text(x, y, text, BUTTON_TEXT_COLOR);
}

void draw_wave_progression(const Game* game, Sector wave, Sector gauge) {
    int text_width, text_height;
    int x, y;

    MLV_Color color = BUTTON_BACKGROUND_COLOR;
    MLV_get_mouse_position(&x, &y);
    if (is_coord_in_sector(wave, x, y)) {
        color = BUTTON_HOVER_COLOR;

        int t = game->time_until_next_wave.next_interval / 60;
        int mana_gain = t * game->player.max_quantity / 100;

        int player_height =
            get_height(game->player.max_quantity, game->player.mana);

        int mana_height = get_height(game->player.max_quantity, mana_gain);
        MLV_draw_filled_rectangle(
            gauge.top_left.x,
            gauge.bottom_right.y - player_height - mana_height, gauge.width,
            mana_height, MLV_rgba(255 - 252, 255 - 3, 255 - 73, 200));
    }

    MLV_get_size_of_text("Wave %d", &text_width, &text_height, game->wave);
    x = wave.top_left.x + wave.width / 2 - text_width / 2;
    y = wave.top_left.y + wave.height / 2 - text_height / 2;

    MLV_draw_filled_rectangle(wave.top_left.x, wave.top_left.y, wave.width,
                              wave.height, color);

    color = MLV_rgba(200, 0, 0, 150);
    int width = game->time_until_next_wave.next_interval * wave.width /
                    (FRAMERATE * TIMER_WAVE) +
                1;
    MLV_draw_filled_rectangle(wave.top_left.x, wave.top_left.y, width,
                              wave.height, color);

    MLV_draw_text(x, y, "Wave %d", BUTTON_TEXT_COLOR, game->wave);
}

void draw_buttons(const GameSectors* sectors) {
    draw_button(sectors->upgrade_button, "Upgrade");
    draw_button(sectors->tower_button, "Tower");
    draw_button(sectors->gem_button, "Gem");
    draw_button(sectors->add_button, "++");
    draw_button(sectors->sub_button, "--");
    draw_button(sectors->pause_button, "Pause");
}

void draw_button_outline(const GameSectors* sectors) {
     for (int y = 0; y < 8; y++) {
        MLV_draw_line(sectors->panel.top_left.x,
                      sectors->upgrade_button.top_left.y + y*CELL_SIZE,
                      sectors->panel.bottom_right.x,
                      sectors->upgrade_button.top_left.y + y*CELL_SIZE,
                      MLV_COLOR_BLACK);
    }
}
