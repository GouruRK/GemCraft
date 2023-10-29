#include <MLV/MLV_all.h>

#include "../include/display_game.h"
#include "../include/field.h"


int main(int argc, char* argv[]) {
    
    // TODO : function when exit

    MLV_create_window("Tower Defense", NULL, WIDTH * CELL_SIZE, HEIGHT * CELL_SIZE);
    
    Field field = create_empty_field();
    field.board[HEIGHT - 2][WIDTH - 2] = TOWER;

    field.board[3][5] = PATH;

    draw_board(field);
    MLV_update_window();

    MLV_wait_seconds(5);
    MLV_free_window();
    return 0;
}
