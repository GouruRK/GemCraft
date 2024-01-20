#include "display/display_game.h"

#include <MLV/MLV_all.h>

#include "utils/color.h"
#include "display/display_const.h"
#include "display/display_tower.h"
#include "display/draw_button.h"
#include "display/draw_gems.h"
#include "display/draw_inventory.h"
#include "display/draw_mana_gauge.h"
#include "display/tooltip.h"
#include "display/display_error.h"
#include "display/display_skill_tree.h"
#include "game_engine/field.h"
#include "game_engine/game.h"
#include "game_engine/monster.h"
#include "game_engine/projectile.h"
#include "game_engine/tower.h"


/**
 * @brief Draw game field
 * 
 * @param field 
 */
static void draw_board(const Field field) {
    // Array of colors for the map
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
            if (field.board[y][x] != TOWER) {
                color = objects_color[field.board[y][x]];
                MLV_draw_filled_rectangle(x*CELL_SIZE, y*CELL_SIZE,
                                          CELL_SIZE, CELL_SIZE, color);
            }
        }
    }

    // horizontal
    for (int y = 0; y < HEIGHT; y++) {
        MLV_draw_line(0, y*CELL_SIZE, WIDTH*CELL_SIZE + PANEL_WIDTH,
                      y*CELL_SIZE, MLV_COLOR_BLACK);
    }

    // vertical
    for (int x = 0; x < WIDTH; x++) {
        MLV_draw_line(x*CELL_SIZE, 0, x*CELL_SIZE, HEIGHT*CELL_SIZE,
                      MLV_COLOR_BLACK);
    }
}

/**
 * @brief Draw a monster
 * 
 * @param m 
 */
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
    MLV_Color monster_color = transform_color(m->color);
    MLV_draw_filled_circle((int)(m->pos.x * CELL_SIZE),
                           (int)(m->pos.y * CELL_SIZE), CELL_SIZE / 3,
                           monster_color);
}

/**
 * @brief Draw a projectile
 * 
 * @param proj 
 */
static void draw_projectile(const Projectile* proj) {
    MLV_Color color = transform_color(proj->source.color);
    MLV_draw_filled_circle((int)(proj->pos.x * CELL_SIZE),
                           (int)(proj->pos.y * CELL_SIZE), CELL_SIZE / 6,
                           color);
}

/**
 * @brief Draw the level of the next gem to be generated 
 * 
 * @param sector 
 * @param level 
 */
static void draw_gem_level(Sector sector, unsigned int level) {
    int text_width, text_height;
    int x, y;

    MLV_get_size_of_text("%d", &text_width, &text_height, level);
    x = sector.top_left.x + sector.width / 2 - text_width / 2;
    y = sector.top_left.y + sector.height / 2 - text_height / 2;

    MLV_draw_filled_rectangle(sector.top_left.x, sector.top_left.y,
                              sector.width, sector.height,
                              BUTTON_BACKGROUND_COLOR);

    MLV_draw_text(x, y, "%d", MLV_COLOR_WHITE, level);
}

/**
 * @brief Display given cost on gauge
 * 
 * @param gauge 
 * @param player 
 * @param cost 
 */
static void display_cost(Sector gauge, Player player, long int cost) {
    if (cost > 0 && cost > player.mana) {
        int height = get_height(player.max_quantity, cost);
        MLV_draw_filled_rectangle(gauge.top_left.x, gauge.bottom_right.y - 1,
                                  gauge.width, -height,
                                  MLV_rgba(252, 3, 73, 200));
    } else if (cost > 0 && cost <= player.mana) {
        int height = get_height(player.max_quantity, cost);
        MLV_draw_filled_rectangle(gauge.top_left.x, gauge.bottom_right.y - 1,
                                  gauge.width, -height,
                                  MLV_rgba(255 - 252, 255 - 3, 255 - 73, 200));
    }
}

/**
 * @brief Display on gauge the cost of elements based on the last event
 * 
 */
static void display_cost_of_element(const Game* game) {
    int cost;
    switch (game->cur_interact.current_action) {
        case SHOWING_UPGRADE_COST:
            cost = mana_require_for_pool(game->player.mana_lvl + 1);
            if (game->player.mana_lvl < 40) {
                cost = mana_require_for_pool(game->player.mana_lvl + 1);
            }
            break;
        case SHOWING_GEM_COST:    
            cost = mana_require_for_gem(game->cur_interact.gem_level);
            break;
        case SHOWING_TOWER_COST:
            cost = get_tower_cost(&(game->field.towers));
            break;
        case SHOWING_GEM_COST_ADD:
            cost = mana_require_for_gem(game->cur_interact.gem_level + 1);
            break;
        case SHOWING_GEM_COST_SUB:
            cost = 0;
            if (game->cur_interact.gem_level) {
                cost = mana_require_for_gem(game->cur_interact.gem_level - 1);
            }
            break;
        default: 
            cost = 0;
            break;
    }
    if (cost) {
        display_cost(game->sectors.gauge, game->player, cost);
    }
}


void draw_game(const Game* game) {
    draw_board(game->field);

    // Draw all monsters
    for (int i = 0; i < game->field.monsters.array_size; i++) {
        draw_monster(&(game->field.monsters.array[i]));
    }

    // Draw towers
    for (int i = 0; i < game->field.towers.cur_len; i++) {
        draw_tower(game->field.towers.lst[i]);
    }

    // Draw right panel
    draw_gauge(game->player, game->sectors.gauge);
    draw_inventory(game->player.inventory, game->sectors.inventory);
    draw_gem_level(game->sectors.gem_lvl, game->cur_interact.gem_level);
    draw_buttons(&(game->sectors));
    draw_wave_progression(game, game->sectors.wave_button, game->sectors.gauge);
    draw_button_outline(&(game->sectors));

    // Draw tower or gem that the player is moving
    if (game->cur_interact.current_action == PLACING_TOWER) {
        draw_tower(game->cur_interact.selected_tower);
    } else if (game->cur_interact.current_action == MOVING_GEM) {
        draw_gem(game->cur_interact.object_pos,
                 game->cur_interact.selected_gem);
        if (game->cur_interact.show_combine_cost) {
            display_cost(game->sectors.gauge, game->player, 100);
        }
    } else if (game->cur_interact.current_action == SHOWING_TOOLTIP) {
        display_tool_tip(game->sectors.window, game->cur_interact.tooltip);
    } else {
        display_cost_of_element(game);
    }
    draw_gauge_numbers(game->player, game->sectors.gauge);

    // Draw projectiles 
    for (int i = 0; i < game->field.projectiles.nb_elt; i++) {
        draw_projectile(&(game->field.projectiles.array[i]));
    }

    // Display an error
    if (game->cur_interact.err.contains_message) {
        display_error(&(game->cur_interact.err), game->sectors.window);
    }

    // Display skill tree
    if (game->game_status == SKILL) {
        display_skill_tree(game);
    }

    MLV_update_window();
}
