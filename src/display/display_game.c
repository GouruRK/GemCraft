#include "display/display_game.h"

#include <MLV/MLV_all.h>

#include "game_engine/field.h"
#include "game_engine/monster.h"
#include "game_engine/projectile.h"
#include "game_engine/game.h"
#include "display/draw_mana_gauge.h"
#include "display/draw_inventory.h"
#include "display/draw_button.h"
#include "display/display_const.h"
#include "display/draw_gems.h"

// Prototype
static void draw_board(const Field field) {
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

static void draw_gem_level(Sector sector, unsigned int level) {
    int text_width, text_height;
    int x, y;

    MLV_get_size_of_text("%d", &text_width, &text_height, level);
    x = sector.top_left.x + sector.width/2 - text_width/2;
    y = sector.top_left.y + sector.height/2 - text_height/2;
    
    MLV_draw_filled_rectangle(sector.top_left.x,
                              sector.top_left.y,
                              sector.width,
                              sector.height,
                              MLV_COLOR_BLACK);
    
    MLV_draw_text(x, y, "%d", MLV_COLOR_WHITE, level);
}

// Prototype
void draw_game(const Game* game) {
    draw_board(game->field);

    // Draw all monsters
    for (int i = 0; i < game->field.monsters.array_size; i++) {
        draw_monster(&(game->field.monsters.array[i]));
    }


    draw_gauge(game->player, game->sectors.panel);
    draw_inventory(game->player.inventory, game->sectors.panel);
    draw_buttons(&(game->sectors));

    // Prototype
    if (game->cur_interact.current_action == PLACING_TOWER) {
        draw_tower(game->cur_interact.selected_tower);
    } else if (game->cur_interact.current_action == MOVING_GEM) {
        draw_gem(game->cur_interact.object_pos, game->cur_interact.selected_gem);
    }

    // Prototype
    for (int i = 0; i < game->field.towers.cur_len; i++) {
        if (game->field.towers.lst[i].hold_gem) {
            draw_gem(game->field.towers.lst[i].pos, game->field.towers.lst[i].gem);
        }
    }

    draw_gem_level(game->sectors.gem_lvl, game->cur_interact.gem_level);
    
    MLV_update_window();
}
