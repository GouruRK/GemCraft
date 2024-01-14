#include <MLV/MLV_all.h>
#include <stdbool.h>

#include "user_event/event.h"
#include "user_event/interact.h"
#include "user_event/tower_placement.h"
#include "user_event/gem_placement.h"
#include "user_event/get_event.h"
#include "user_event/error_message.h"
#include "user_event/events.h"
#include "user_event/skill_tree.h"
#include "game_engine/gem.h"
#include "game_engine/game.h"
#include "game_engine/player.h"
#include "game_engine/inventory.h"
#include "game_engine/score.h"
#include "game_engine/tower.h"
#include "game_engine/nest.h"
#include "display/display_game.h"
#include "display/game_sectors.h"
#include "display/display_const.h"
#include "display/display_skill_tree.h"
#include "utils/errors.h"

void exit_function(void* data) {
    int* stop = (int*)data;
    *stop = 1;
}

/**
 * @brief Set interaction to select a gem from a tower.
 *        Tower coordinates on screen are (x, y)
 *        where the player clicked
 * 
 * @param game
 */
static Error pick_up_gem_from_field(Game* game) {
    int x, y;
    MLV_get_mouse_position(&x, &y);
    Gem gem;
    if (unload_gem(&(game->field), &gem, init_scaled_position(x, y)) == OK) {
        return set_interact_gem_movement(&(game->cur_interact), gem);
    }
    return OK;
}

/**
 * @brief Set interaction to select a gem from the inventory.
 *        Selected gem coordinates on screen are (x, y) 
 *        where the player clicked
 * 
 * @param game
 */
static Error pick_up_gem_from_inventory(Game* game) {
    int x, y;
    Gem gem;
    MLV_get_mouse_position(&x, &y);

    int inventory_index = from_coord_to_index(&(game->sectors), x, y);

    if (!game->player.inventory.array[inventory_index].empty) {
        remove_gem_at(&(game->player.inventory), &gem, inventory_index);
        return set_interact_gem_movement(&(game->cur_interact), gem);
    }
    return OK;
}

/**
 * @brief Drop the selected gem on the inventory square at coordinates (x, y).
 *        Store the gem if the inventory is empty, else mix.
 * 
 * @param game
 */
static Error drop_gem_on_inventory(Game* game) {
    int x, y;
    Gem gem, res;
    Error err;

    MLV_get_mouse_position(&x, &y);
    int inventory_index = from_coord_to_index(&(game->sectors), x, y);

    if (game->player.inventory.array[inventory_index].empty) { 
        // if this inventory place is empty, juste place the gem 
        store_gem_at(&(game->player.inventory), game->cur_interact.selected_gem,
                     inventory_index);
        reset_interaction(&(game->cur_interact));
    } else {
        // if this inventory place isn't empty, mix the selected gem with
        //  the one currently store
        remove_gem_at(&(game->player.inventory), &gem, inventory_index);
        err = combine_gem(&(game->player), game->cur_interact.selected_gem, 
                          gem, &res);
        if (err != OK) {
            // if gems cannot be combined, store the stored gem 
            // in the inventory again
            store_gem_at(&(game->player.inventory), gem, inventory_index);
            return err;
        } else {
            // store the result of gem mixing
            store_gem_at(&(game->player.inventory), res, inventory_index);
            reset_interaction(&(game->cur_interact));
        }
    }
    return OK;
}

/**
 * @brief Drop the selected gem on a tower of coordinates on screen (x, y).
 * 
 * @param game
 */
static Error drop_gem_on_field(Game* game) {
    int x, y;
    MLV_get_mouse_position(&x, &y);
    Error err = load_gem(&(game->field), game->cur_interact.selected_gem,
                         init_scaled_position(x, y)); 
    
    if (err == OK) {
        reset_interaction(&(game->cur_interact));
    }
    return err;
}

/**
 * @brief Summon a gem an store in in the inventory
 * 
 * @param game
 */
static Error summon_gem(Game* game) {
    Gem gem;
    Error err;
    if (is_inventory_full(&(game->player.inventory))) {
        return INVENTORY_FULL;
    }
    err = generate_gem(&(game->player), game->cur_interact.gem_level, &gem);
    if (err != OK) {
        return err;
    }
    game->cur_interact.gem_level = 0;
    return add_inventory(&(game->player.inventory), gem);
}

/**
 * @brief Add a level to generate a gem
 * 
 * @param game 
 */
static Error add_gem_level(Game* game) {
    int mana = mana_require_for_gem(game->cur_interact.gem_level + 1);
    if (game->player.mana >= mana) {
        game->cur_interact.gem_level++;
        return OK;
    }
    return NOT_ENOUGHT_MANA;
}

/**
 * @brief Remove a level to generate a gem
 * 
 * @param game 
 */
static Error sub_gem_level(Game* game) {
    if (game->cur_interact.gem_level) {
        game->cur_interact.gem_level--;
    }
    return OK;
}

/**
 * @brief Summon a new tower and change interaction
 * 
 * @param game 
 */
static Error summon_tower(Game* game) {
    if (game->player.mana >= get_tower_cost(&(game->field.towers))) {
        set_interact_tower_placement(&(game->cur_interact), 
                                     init_tower_at_mouse(game->sectors.panel));
        return OK;
    }
    return NOT_ENOUGHT_MANA;
}

/**
 * @brief Summon a new wave
 * 
 * @param game 
 */
static Error summon_wave(Game* game) {
    int generate = add_wave_nest(&(game->field.nest), &(game->score),
                                 game->wave);
    if (game->wave > 0 && generate) {
        int t = game->time_until_next_wave.next_interval / 60;
        int mana_win = t * game->player.max_quantity / 100;
        game->player.mana = min(game->player.max_quantity, 
                                game->player.mana + mana_win);
    }

    if (generate) {
        game->time_until_next_wave = init_clock(TIMER_WAVE, -1);
        decrease_clock(&game->time_until_next_wave);
        game->wave++;

        if (!(game->wave % WAVE_OFFSET)) {
            game->game_status = SKILL;
            game->tree = init_skill_tree(game->wave);
            init_sectors(&(game->tree), game->sectors.window);
        }
        
        return OK;
    }

    return WAVE_IS_ALREADY_SPAWNING;
}

/**
 * @brief Place a tower in field
 * 
 * @param game 
 */
static Error place_tower_in_field(Game* game) {
    return drop_tower(&(game->cur_interact), &(game->field), &(game->player));
}

/**
 * @brief Cancel tower placement
 * 
 * @param game 
 */
static Error cancel_tower_placement(Game* game) {
    cancel_interaction(&(game->cur_interact));
    return OK;
}

/**
 * @brief Upgrade mana pool's level
 * 
 * @param game 
 */
static Error upgrade_pool(Game* game) {
    return upgrade_mana_pool(&(game->player));
}

/**
 * @brief Change interaction to showing tooltip, and select the correct object
 *        to give information
 * 
 * @param game 
 */
static Error display_tooltip(Game* game) {
    int x, y;
    MLV_get_mouse_position(&x, &y);
    Position pos = init_position(x, y);
    if (is_pos_in_sector(game->sectors.inventory, pos)) {
        int inventory_index = from_coord_to_index(&(game->sectors), x, y);
        Inventory inv = game->player.inventory;
        if (!inv.array[inventory_index].empty) {
            set_interact_tooltip(&(game->cur_interact),
                    init_gem_tooltip(inv.array[inventory_index].gem, pos));
        }
    } else if (is_pos_in_sector(game->sectors.field, pos)) {
        Tower* tower;
        if (get_tower(&(game->field), &tower,
                init_scaled_position(x, y)) != OK) {
            return OK;
        }
        set_interact_tooltip(&(game->cur_interact), 
            init_tower_tooltip(*tower, pos));
    }
    return OK;
}

/**
 * @brief Reset current interaction
 * 
 * @param game 
 */
static Error reset_current_interaction(Game* game) {
    reset_interaction(&(game->cur_interact));
    return OK;
}

/**
 * @brief Reset current interaction if possible
 * 
 * @param game 
 */
static Error reset_overwritable_events(Game* game) {
    reset_overwritable_interaction(&game->cur_interact);
    return OK;
}

/**
 * @brief Change interaction to display the upgrade cost of the mana pool
 * 
 * @param game 
 */
static Error show_upgrade_cost(Game* game) {
    set_interact_show_upgrade_cost(&(game->cur_interact));
    return OK;
}

/**
 * @brief Change interaction to display the cost of the next tower
 * 
 * @param game 
 */
static Error show_tower_cost(Game* game) {
    set_interact_show_tower_cost(&(game->cur_interact));
    return OK;
}

/**
 * @brief Change interaction to display the cost of creating a gem at 
 *        its current selected level
 * 
 * @param game 
 */
static Error show_gem_cost(Game* game) {
    set_interact_show_gem_cost(&(game->cur_interact));
    return OK;
}

/**
 * @brief Change interaction to display the cost of creating a gem at 
 *        its selected level + 1
 * 
 * @param game 
 */
static Error show_gem_cost_add(Game* game) {
    set_interact_show_gem_cost_add(&(game->cur_interact));
    return OK;
}

/**
 * @brief Change interaction to display the cost of creating a gem at 
 *        its selected level - 1
 * 
 * @param game 
 */
static Error show_gem_cost_sub(Game* game) {
    set_interact_show_gem_cost_sub(&(game->cur_interact));
    return OK;
}

/**
 * @brief Change interaction to display the cost of combining two gems
 * 
 * @param game 
 * @return
 */
static Error show_combine_cost(Game* game) {
    int x, y;
    MLV_get_mouse_position(&x, &y);
    if (is_coord_in_sector(game->sectors.inventory, x, y)) {
        int inventory_index = from_coord_to_index(&(game->sectors), x, y);
        if (!game->player.inventory.array[inventory_index].empty) {
            game->cur_interact.show_combine_cost = true;
        } else {
            game->cur_interact.show_combine_cost = false;
        }
    } else {
        game->cur_interact.show_combine_cost = false;
    }
    return OK;
}

/**
 * @brief Cancel a gem movement and place the gem in the inventory
 * 
 * @param game 
 * @return
 */
static Error cancel_gem_movement(Game* game) {
    if (is_inventory_full(&(game->player.inventory))) {
        return INVENTORY_FULL;
    }

    add_inventory(&(game->player.inventory), game->cur_interact.selected_gem);
    reset_interaction(&(game->cur_interact));
    return OK;
}

// Link between events and functions to apply them
event_function func[] = {
    [NO_EVENT] = reset_overwritable_events,
    [SUMMON_WAVE] = summon_wave,
    [SUMMON_TOWER] = summon_tower,
    [SUMMON_GEM] = summon_gem,
    [PLACE_TOWER] = place_tower_in_field,
    [CANCEL_PLACING_TOWER] = cancel_tower_placement,
    [CANCEL_PLACING_GEM] = cancel_gem_movement,
    [PICK_GEM_FROM_FIELD] = pick_up_gem_from_field,
    [PICK_GEM_FROM_INVENTORY] = pick_up_gem_from_inventory,
    [DROP_GEM_IN_INVENTORY] = drop_gem_on_inventory,
    [DROP_GEM_IN_FIELD] = drop_gem_on_field,
    [ADD_GEM_LEVEL] = add_gem_level,
    [SUB_GEM_LEVEL] = sub_gem_level,
    [SUMMON_GEM] = summon_gem,
    [UPGRADE_MANA_POOL] = upgrade_pool,
    [SHOW_TOOLTIP] = display_tooltip,
    [HIDE_TOOLTIP] = reset_current_interaction,
    [SHOW_UPGRADE_COST] = show_upgrade_cost,
    [SHOW_GEM_COST] = show_gem_cost,
    [SHOW_TOWER_COST] = show_tower_cost,
    [SHOW_GEM_COST_ADD] = show_gem_cost_add,
    [SHOW_GEM_COST_SUB] = show_gem_cost_sub,
    [SHOW_COMBINE_COST] = show_combine_cost
};

/**
 * @brief Process current event
 * 
 * @param game 
 * @return 'true' to quit the game, else 'false'
 */
bool process_event(Game* game) {
    Event event = get_event(game->cur_interact, &(game->sectors));
    if (event == QUIT) {
        return true;
    } else if (event == CHANGE_GAME_STATUS) { // need to do this because when
                                              // game is paused, buttons except
                                              // the pause one no longer works 
        game->game_status = !(game->game_status);
    }  else if (game->game_status != PAUSE) {
        event_function f;
        if ((f = func[event])) {
            Error err = f(game);
            if (err != OK) {
                game->cur_interact.err = init_error_message(event, err);
            }
        }
        
        if (game->cur_interact.current_action == PLACING_TOWER) {
            update_tower_placement(game->sectors.panel, 
                                   &(game->cur_interact.selected_tower));
        } else if (game->cur_interact.current_action == MOVING_GEM || 
                   game->cur_interact.current_action == SHOWING_COMBINE_COST) {
            update_gem_movement(&(game->sectors), &(game->cur_interact));
        }
    }
    return false;
}

void wait_event(int* terminated) {
    MLV_Keyboard_modifier mod;
    MLV_Keyboard_button sym;
    MLV_Button_state state;

    *terminated = 0;
    // intel on mouse
    MLV_Mouse_button mouse_but;
    while (!(*terminated)) {
        MLV_Event event = MLV_get_event(&sym, &mod, NULL, NULL, NULL, NULL,
                                        NULL, &mouse_but, &state);
        if (event) {
            break;
        }
        MLV_update_window();
    }
}
