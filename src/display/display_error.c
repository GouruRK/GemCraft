#include "display/display_error.h"

#include <MLV/MLV_all.h>

#include "user_event/error_message.h"
#include "utils/sector.h"

void display_error(const ErrorMessage* err, Sector window) {
    if (!err->contains_message) {
        return;
    }

    static int x_padding = 15, y_padding = 15;
    static int top_y = 10;

    int w, h;
    MLV_get_size_of_text(err->message, &w, &h);
    
    int rectangle_width = w + x_padding*2;
    int rectangle_height = h + y_padding*2;

    int top_x = window.width/2 - rectangle_width/2;
    
    MLV_draw_filled_rectangle(top_x, top_y, rectangle_width, rectangle_height,
                              MLV_rgba(255, 0, 0, 200));
    
    MLV_draw_text(top_x + x_padding, top_y + y_padding, err->message, 
                  MLV_COLOR_WHITE);

}
