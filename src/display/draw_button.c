#include "display/draw_button.h"

#include <MLV/MLV_all.h>

#include "utils/sector.h"
#include "display/game_sectors.h"

// TODO : save somehow computation of position depending the text
// because a text position for a button is always the same
// and don't need to be re-computed each time the function is called

/**
 * @brief Draw a button in the given sector with text as its label
 * 
 * @param gem_button 
 * @param text 
 */
static void draw_button(Sector gem_button, char* text, MLV_Color background_color, MLV_Color text_color) {
    int text_width, text_height;
    int x, y;

    MLV_get_size_of_text(text, &text_width, &text_height);
    x = gem_button.top_left.x + gem_button.width/2 - text_width/2;
    y = gem_button.top_left.y + gem_button.height/2 - text_height/2;
    
    MLV_draw_filled_rectangle(gem_button.top_left.x,
                              gem_button.top_left.y,
                              gem_button.width,
                              gem_button.height,
                              background_color);
    
    MLV_draw_text(x, y, text, text_color);
}

void draw_buttons(const GameSectors* sectors) {
    draw_button(sectors->upgrade_button, "Upgrade", MLV_COLOR_YELLOW, MLV_COLOR_BLACK);
    draw_button(sectors->gem_button, "Gem", MLV_COLOR_YELLOW, MLV_COLOR_BLACK);
    draw_button(sectors->tower_button, "Tower", MLV_COLOR_YELLOW, MLV_COLOR_BLACK);
    draw_button(sectors->add_button, "++", MLV_COLOR_BLACK, MLV_COLOR_WHITE);
    draw_button(sectors->sub_button, "--", MLV_COLOR_BLACK, MLV_COLOR_WHITE);
    draw_button(sectors->wave_button, "Wave", MLV_COLOR_YELLOW, MLV_COLOR_BLACK);
    draw_button(sectors->pause_button, "Pause", MLV_COLOR_YELLOW, MLV_COLOR_BLACK);
}
