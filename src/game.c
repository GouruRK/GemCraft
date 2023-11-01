#include "../include/game.h"
#include "../include/errors.h"
#include "../include/tower.h"

Error place_tower(Game* game, Tower tower) {
    int cost = game->towers.next_tower_cost;
    Error err;

    if (game->player.mana < cost) {
        return NOT_ENOUGHT_MANA;
    }

    if (get_field(game->field, tower.pos) != EMPTY) {
        return NON_EMPTY_PLACE;
    }

    err = add_tower_array(&(game->towers), tower);
    if (err != OK) {
        return err;
    }

    game->field.board[tower.pos.y][tower.pos.x] = TOWER;
    game->player.mana -= cost;
    return OK;
}