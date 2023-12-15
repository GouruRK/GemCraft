#include <MLV/MLV_all.h>
#include <stdbool.h>

#include "user_event/event.h"
#include "user_event/interact.h"
#include "user_event/tower_placement.h"
#include "game_engine/game.h"
#include "display/display_game.h"

Event get_event(Interaction interaction) {
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
                // if (game.field.nest.monster_remaining == 0) {
                //     fprintf(stderr, "%c\n", sym);
                //     init_new_wave(&(game.field.nest), game.wave);
                //     game.wave++;
                // }
                // break;
            case 't': // place a tower
                return SUMMON_TOWER;
                // if (game.player.mana > game.field.towers.next_tower_cost) {
                //     set_interact_tower_placement(&(game.cur_interact), init_tower_at_mouse(CELL_SIZE));
                // }
                // break;
            default:
                break;
            }
    } else if(event == MLV_MOUSE_BUTTON) {
        switch (mouse_but) {
            case MLV_BUTTON_LEFT:
                if (interaction.current_action == PLACING_TOWER) {
                    return PLACE_TOWER;
                }
                // if (game.cur_interact.current_action == PLACING_TOWER) {
                //     drop_tower(&(game.cur_interact), &(game.field), &(game.player));
                // }
                // break;
            case MLV_BUTTON_RIGHT:
                if (interaction.current_action == PLACING_TOWER) {
                    return CANCEL_PLACING_TOWER;
                }
                // cancel_interaction(&(game.cur_interact));
                // break;
            default:
                break;
        }
    }
    return NO_EVENT;
}

bool process_event(Game* game) {
    switch (get_event(game->cur_interact)) {
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
                set_interact_tower_placement(&(game->cur_interact), init_tower_at_mouse(CELL_SIZE));
            }
            return false;
        case PLACE_TOWER:
            drop_tower(&(game->cur_interact), &(game->field), &(game->player));
            return false;
        case CANCEL_PLACING_TOWER:
            cancel_interaction(&(game->cur_interact));
            return false;
        default:
            return false;
    }
}