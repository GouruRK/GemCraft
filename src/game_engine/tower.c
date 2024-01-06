#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "game_engine/tower.h"
#include "game_engine/gem.h"
#include "utils/position.h"
#include "utils/errors.h"

Tower init_tower(Position pos) {
    Tower tower;
    tower.pos = pos;
    tower.hold_gem = false;

    tower.deploy_timer = init_clock(-1, -1);
    tower.shoot_interval = init_clock(0.5, -1);

    return tower;
}

Error add_gem_to_tower(Tower* tower, Gem gem) {
    if (tower->hold_gem) {
        return NON_EMPTY_TOWER;
    }
    tower->gem = gem;
    tower->hold_gem = true;

    tower->deploy_timer = init_clock(-1, 2);

    fprintf(stderr, "Tower mounted and loaded\n");

    return OK;
}

Error remove_gem_from_tower(Tower* tower, Gem* gem) {
    if (!(tower->hold_gem)) {
        return EMPTY_TOWER;
    } 
    *gem = tower->gem;
    tower->hold_gem = false;
    return OK;
}

TowerArray create_tower_array(void) {
    TowerArray array;
    array.cur_len = 0;
    array.next_tower_cost = 0;
    return array;
}

Error add_tower_array(TowerArray* array, Tower tower) {
    if (array->cur_len == MAX_TOWER) {
        return TOWER_ARRAY_FULL;
    }
    array->lst[array->cur_len] = tower;
    
    if (array->cur_len >= 2) { // first three towers are free
        if (!(array->next_tower_cost)) {
            array->next_tower_cost = 100;
        } else {
            array->next_tower_cost *= 2;
        }
    }
    array->cur_len++;
    return OK;
}

void update_clock_tower(Tower* tower) {
    decrease_clock(&tower->deploy_timer);
    decrease_clock(&tower->shoot_interval);
}
