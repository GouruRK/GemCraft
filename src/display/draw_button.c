#include "display/draw_button.h"

#include <MLV/MLV_all.h>

#include "utils/sector.h"
#include "display/game_sectors.h"
#include "game_engine/game.h"

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
    x = button.top_left.x + button.width/2 - text_width/2;
    y = button.top_left.y + button.height/2 - text_height/2;


    MLV_draw_filled_rectangle(button.top_left.x,
                              button.top_left.y,
                              button.width,
                              button.height,
                              color);
    
    MLV_draw_text(x, y, text, BUTTON_TEXT_COLOR);
}

void draw_wave_progression(int remaining_time, int nb_wave, Sector wave) {
    int text_width, text_height;
    int x, y;

    MLV_Color color = BUTTON_BACKGROUND_COLOR;
    MLV_get_mouse_position(&x, &y);
    if (is_coord_in_sector(wave, x, y)) {
        color = BUTTON_HOVER_COLOR;
    }
    
    MLV_get_size_of_text("Wave", &text_width, &text_height);
    x = wave.top_left.x + wave.width/2 - text_width/2;
    y = wave.top_left.y + wave.height/2 - text_height/2;


    MLV_draw_filled_rectangle(wave.top_left.x,
                              wave.top_left.y,
                              wave.width,
                              wave.height,
                              color);
    
    color = MLV_rgba(200, 0, 0, 150);
    int width = remaining_time * wave.width / (FRAMERATE * TIMER_WAVE) + 1;
    MLV_draw_filled_rectangle(wave.top_left.x, wave.top_left.y,
                              width, wave.height, color);

    MLV_draw_text(x, y, "Wave", BUTTON_TEXT_COLOR);

}

void draw_buttons(const GameSectors* sectors) {
    draw_button(sectors->upgrade_button, "Upgrade");
    draw_button(sectors->gem_button, "Gem");
    draw_button(sectors->tower_button, "Tower");
    draw_button(sectors->add_button, "++");
    draw_button(sectors->sub_button, "--");
    draw_button(sectors->pause_button, "Pause");
}
