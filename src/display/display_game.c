#include "display/display_game.h"

#include <MLV/MLV_all.h>

#include "game_engine/field.h"
#include "game_engine/monster.h"
#include "game_engine/projectile.h"
#include "game_engine/game.h"
#include "user_event/tower_placement.h"
#include "display/draw_mana_gauge.h"

// Prototype
static void draw_board(Field field) {
    MLV_Color objects_color[6] = {
        MLV_COLOR_BROWN4,  // Tower
        MLV_COLOR_RED,     // Nest
        MLV_COLOR_GREEN,   // Camp
        MLV_COLOR_GREY,    // Empty
        MLV_COLOR_WHITE    // Path
    };
    MLV_Color color;
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            color = objects_color[field.board[y][x]];
            MLV_draw_filled_rectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE,
                                      CELL_SIZE, color);
        }
    }

    // horizontal
    for (int y = 0; y < HEIGHT; y++) {
        MLV_draw_line(0, y * CELL_SIZE, WIDTH * CELL_SIZE, y * CELL_SIZE,
                      MLV_COLOR_BLACK);
    }

    // vertical
    for (int x = 0; x < WIDTH; x++) {
        MLV_draw_line(x * CELL_SIZE, 0, x * CELL_SIZE, HEIGHT * CELL_SIZE,
                      MLV_COLOR_BLACK);
    }
}

// Prototype
static void draw_monster(const Monster* m) {
    if (!is_alive(m)) {
        return;
    };

    // Draw health bar
    MLV_draw_filled_rectangle((int)(m->pos.x * CELL_SIZE) - 10,
                              (int)(m->pos.y * CELL_SIZE) - CELL_SIZE / 2, 20,
                              4, MLV_COLOR_RED);
    int health_remaining = m->health * 20 / m->max_health;
    MLV_draw_filled_rectangle((int)(m->pos.x * CELL_SIZE) - 10,
                              (int)(m->pos.y * CELL_SIZE) - CELL_SIZE / 2,
                              health_remaining, 4, MLV_COLOR_GREEN);
    
    // Draw the monster
    MLV_draw_filled_circle((int)(m->pos.x * CELL_SIZE),
                           (int)(m->pos.y * CELL_SIZE), CELL_SIZE / 3,
                           MLV_COLOR_BLUE);
}

// Prototype
static void draw_projectile(const Projectile* proj) {
    MLV_draw_filled_circle((int)(proj->pos.x * CELL_SIZE),
                           (int)(proj->pos.y * CELL_SIZE), CELL_SIZE / 6,
                           MLV_COLOR_DARK_GREEN);
}

// Prototype
static void draw_tower(const Tower tower) {
    Position center = cell_center(tower.pos);

    MLV_draw_filled_circle((int)(center.x * CELL_SIZE),
                           (int)(center.y * CELL_SIZE),
                           CELL_SIZE / 3, 
                           MLV_COLOR_PINK1);
}

// Prototype
void draw_game(Game* game) {
    draw_board(game->field);

    // Draw all monsters
    for (int i = 0; i < game->field.monsters.array_size; i++) {
        draw_monster(&(game->field.monsters.array[i]));
    }

    // Prototype
    if (game->cur_interact.current_action == PLACING_TOWER) {
        update_tower_placement(&(game->cur_interact.selected_tower), CELL_SIZE);
        draw_tower(game->cur_interact.selected_tower);
    }

    draw_gauge(game->player, game->sections.inventory_section);

    MLV_update_window();
}
