#include "display/game_section.h"

#include "display/display_game.h"
#include "utils/position.h"
#include "utils/sector.h"

GameSection init_custom_game_section(Sector field, Sector inventory) {
    GameSection sections;
    sections.field_section = field;
    sections.inventory_section = inventory;
    return sections;
}

GameSection init_game_section(int width, int height) {
    return init_custom_game_section(
        init_sector(init_position(0, 0), init_position(width * CELL_SIZE, height * CELL_SIZE)),
        init_sector(init_position(width * CELL_SIZE, 0), init_position(width * CELL_SIZE + INVENTORY_WIDTH, height * CELL_SIZE))
    );
}
