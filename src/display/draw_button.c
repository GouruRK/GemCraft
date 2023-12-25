#include "display/draw_button.h"

#include <MLV/MLV_all.h>

#include "utils/sector.h"

void draw_button(Sector gem_button) {
    static int init = 0, text_width, text_height;
    static int x, y;
    static char* text = "Gem";

    // this if block is only executed the first time the function is called
    if (!init) {
        // position calculation is always the same
        MLV_get_size_of_text(text, &text_width, &text_height);
        x = gem_button.top_left.x + gem_button.width/2 - text_width/2;
        y = gem_button.top_left.y + gem_button.height/2 - text_height/2;
        init = 1;
    }
    
    MLV_draw_filled_rectangle(gem_button.top_left.x,
                              gem_button.top_left.y,
                              gem_button.width,
                              gem_button.height,
                              MLV_COLOR_YELLOW);
    
    MLV_draw_text(x, y, text, MLV_COLOR_BLACK);
}
