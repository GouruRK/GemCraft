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

void draw_buttons(const GameSectors* sectors) {
    draw_button(sectors->upgrade_button, "Upgrade");
    draw_button(sectors->gem_button, "Gem");
    draw_button(sectors->tower_button, "Tower");
    draw_button(sectors->add_button, "++");
    draw_button(sectors->sub_button, "--");
    draw_button(sectors->wave_button, "Wave");
    draw_button(sectors->pause_button, "Pause");
}
