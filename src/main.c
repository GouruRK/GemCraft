#include <MLV/MLV_all.h>
#include <time.h>
#include <stdlib.h>

#include "../include/display_game.h"
#include "../include/field.h"
#include "../include/generation.h"

int main(int argc, char* argv[]) {
    srand(time(NULL));

    // TODO : function when exit

    MLV_create_window("Tower Defense", NULL, WIDTH * CELL_SIZE, HEIGHT * CELL_SIZE);
    
    Field field = generate_field();

    draw_board(field);
    MLV_update_window();

    MLV_wait_seconds(5);
    MLV_free_window();
    return 0;
}
