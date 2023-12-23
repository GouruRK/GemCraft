#include <MLV/MLV_all.h>
#include <stdbool.h>

#include "user_event/event.h"
#include "user_event/interact.h"
#include "user_event/tower_placement.h"
#include "user_event/gem_placement.h"
#include "game_engine/game.h"
#include "display/display_game.h"
#include "display/game_sectors.h"
#include "display/display_const.h"

void exit_function(void* data) {
    int* stop = (int*)data;
    *stop = 1;
}

/**
 * @brief Get the current event
 * 
 * @param interaction current player interaction
 * @return current event
 */
static Event get_event(Interaction interaction, const GameSectors* sectors) {
    // intel on keyboard
    MLV_Keyboard_modifier mod;
    MLV_Keyboard_button sym;
    MLV_Button_state state;
    static MLV_Button_state prev_state;

    // intel on mouse
    MLV_Mouse_button mouse_but;

    MLV_Event event = MLV_get_event(&sym, &mod, NULL, NULL, NULL, NULL, NULL, &mouse_but,
                              &state);

    if (state == prev_state) { // to prevent placing a gem right after picking it
        return NO_EVENT;
    } 
    prev_state = state;

    if (event == MLV_KEY) {
        switch (sym) {
            case 'q':  // Quit the game
                return QUIT;
            case 'w': // Summon a wave
                return SUMMON_WAVE;
            case 't': // place a tower
                if (interaction.current_action == NO_ACTION) {
                    return SUMMON_TOWER;
                }
                return NO_EVENT;
            default:
                break;
            }
    } else if(event == MLV_MOUSE_BUTTON) {
        int x, y;
        MLV_get_mouse_position(&x, &y);
        switch (mouse_but) {
            case MLV_BUTTON_LEFT:
                if (interaction.current_action == PLACING_TOWER && is_coord_in_sector(sectors->field, x, y)) {
                    return PLACE_TOWER;
                }
                if (interaction.current_action == MOVING_GEM) {
                    return PLACE_GEM;
                }
                // TODO : check on button first before checking for gems movement
                // Gem can be moved from anywhere (field to inventory, inventory to inventory, inventory to fields)
                if (interaction.current_action == NO_ACTION) {
                    return MOVE_GEM;
                }
            case MLV_BUTTON_RIGHT:
                if (interaction.current_action == PLACING_TOWER) {
                    return CANCEL_PLACING_TOWER;
                }
            default:
                break;
        }
    }
    return NO_EVENT;
}

/**
 * @brief Set interaction to select a gem from a tower.
 *        Tower coordinates on screen are (x, y)
 *        where the player clicked
 * 
 * @param game 
 * @param x mouse abscissa
 * @param y mouse ordinate
 */
static void pick_up_gem_from_field(Game* game, int x, int y) {
    Gem gem;
    if (unload_gem(&(game->field), &gem, init_scaled_position(x, y)) == OK) {
        set_interact_gem_movement(&(game->cur_interact), gem);
    }
}

/**
 * @brief Set interaction to select a gem from the inventory.
 *        Selected gem coordinates on screen are (x, y) 
 *        where the player clicked
 * 
 * @param game 
 * @param x mouse abscissa
 * @param y mouse ordinate
 */
static void pick_up_gem_from_inventory(Game* game, int x, int y) {
    Gem gem;
    int inventory_index = from_coord_to_index(&(game->sectors), x, y);

    if (!game->player.inventory.array[inventory_index].empty) {
        remove_gem_at(&(game->player.inventory), &gem, inventory_index);
        set_interact_gem_movement(&(game->cur_interact), gem);
    }
}

/**
 * @brief Drop the selected gem on the inventory square at coordinates (x, y).
 *        Store the gem if the inventory is empty, else mix.
 * 
 * @param game 
 * @param x mouse abscissa
 * @param y mouse ordinate
 */
static void drop_gem_on_inventory(Game* game, int x, int y) {
    Gem gem, res;
    int inventory_index = from_coord_to_index(&(game->sectors), x, y);

    if (game->player.inventory.array[inventory_index].empty) { 
        // if this inventory place is empty, juste place the gem 
        store_gem_at(&(game->player.inventory), game->cur_interact.selected_gem, inventory_index);
        reset_interaction(&(game->cur_interact));
    } else {
        // if this inventory place isn't empty, mix the selected gem with the one currently store
        remove_gem_at(&(game->player.inventory), &gem, inventory_index);
        if (combine_gem(&(game->player), game->cur_interact.selected_gem, gem, &res) != OK) {
            // if gems cannot be combined, store the stored gem in the inventory again
            store_gem_at(&(game->player.inventory), gem, inventory_index);
        } else {
            // store the result of gem mixing
            store_gem_at(&(game->player.inventory), res, inventory_index);
            reset_interaction(&(game->cur_interact));
        }
    }
}

/**
 * @brief Drop the selected gem on a tower of coordinates on screen (x, y).
 * 
 * @param game 
 * @param x mouse abscissa
 * @param y mouse ordinate
 */
static void drop_gem_on_field(Game* game, int x, int y) {
    if (load_gem(&(game->field), game->cur_interact.selected_gem, init_scaled_position(x, y)) == OK) {
        reset_interaction(&(game->cur_interact));
    }
}

bool process_event(Game* game) {
    int x, y;
    MLV_get_mouse_position(&x, &y);
    switch (get_event(game->cur_interact, &(game->sectors))) {
        case QUIT:
            return true;
        case SUMMON_WAVE:
            if (game->field.nest.monster_remaining == 0) {
                init_new_wave(&(game->field.nest), game->wave);
                game->wave++;
            }
            return false;
        case SUMMON_TOWER:
            if (game->player.mana > game->field.towers.next_tower_cost) {
                set_interact_tower_placement(&(game->cur_interact), init_tower_at_mouse(game->sectors.panel));
            }
            return false;
        case PLACE_TOWER:
            drop_tower(&(game->cur_interact), &(game->field), &(game->player));
            return false;
        case CANCEL_PLACING_TOWER:
            cancel_interaction(&(game->cur_interact));
            return false;
        case MOVE_GEM:
            if (is_coord_in_sector(game->sectors.field, x, y)) {
                pick_up_gem_from_field(game, x, y);    
            } else if (is_coord_in_sector(game->sectors.inventory, x, y)) {
                pick_up_gem_from_inventory(game, x, y);
            }
            break; // here break to update the selected object position
        case PLACE_GEM:
            if (is_coord_in_sector(game->sectors.inventory, x, y)) {
                drop_gem_on_inventory(game, x, y);
            } else if (is_coord_in_sector(game->sectors.field, x, y)) {
                drop_gem_on_field(game, x, y);
            }
            return false;
        default:
            break;
    }

    if (game->cur_interact.current_action == PLACING_TOWER) {
        update_tower_placement(game->sectors.panel, &(game->cur_interact.selected_tower));
    } else if (game->cur_interact.current_action == MOVING_GEM) {
        update_gem_movement(&(game->cur_interact));
    }
    return false;
}
