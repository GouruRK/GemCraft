#include <MLV/MLV_all.h>
#include <stdbool.h>

#include "user_event/event.h"
#include "user_event/interact.h"
#include "user_event/tower_placement.h"
#include "user_event/gem_placement.h"
#include "game_engine/game.h"
#include "display/display_game.h"
#include "display/game_sectors.h"

void exit_function(void* data) {
    int* stop = (int*)data;
    *stop = 1;
}

Event get_event(Interaction interaction, const GameSectors* sectors) {
    // intel on keyboard
    MLV_Keyboard_modifier mod;
    MLV_Keyboard_button sym;
    MLV_Button_state state;

    // intel on mouse
    MLV_Mouse_button mouse_but;

    MLV_Event event = MLV_get_event(&sym, &mod, NULL, NULL, NULL, NULL, NULL, &mouse_but,
                              &state);

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
                return MOVE_GEM;
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

bool process_event(Game* game) {
    int x, y, inventory_index;
    Gem gem;
    switch (get_event(game->cur_interact, &(game->sectors))) {
        case QUIT:
            return true;
        case SUMMON_WAVE:
            if (game->field.nest.monster_remaining == 0) {
                fprintf(stderr, "SUMMON_WAVE\n");
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
            MLV_get_mouse_position(&x, &y);
            if (is_coord_in_sector(game->sectors.field, x, y)) { // if gem is picked up from the field
                break;
            } else if (is_coord_in_sector(game->sectors.inventory, x, y)) { // if gem is picked up from the inventory
                inventory_index = from_coord_to_index(&(game->sectors), x, y);
                if (!game->player.inventory.array[inventory_index].empty) {
                    remove_gem_at(&(game->player.inventory), &gem, inventory_index);
                    set_interact_gem_movement(&(game->cur_interact), gem);
                }
            }
            break;
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
