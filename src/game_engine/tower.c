#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "game_engine/tower.h"
#include "game_engine/gem.h"
#include "utils/position.h"
#include "utils/errors.h"

//--------------------------------Tower related---------------------------------

Tower init_tower(Position pos) {
    Tower tower;
    tower.pos = pos;
    tower.hold_gem = false;

    tower.deploy_timer = init_clock(-1, -1);
    tower.shoot_interval = init_clock(-1, 0);

    return tower;
}

Error add_gem_to_tower(Tower* tower, Gem gem) {
    if (tower->hold_gem) {
        return NON_EMPTY_TOWER;
    }
    tower->gem = gem;
    tower->hold_gem = true;

    tower->deploy_timer = init_clock(-1, 2);

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

//----------------------------Tower array related-------------------------------

TowerArray init_tower_array(void) {
    TowerArray array;
    array.cur_len = 0;
    array.next_tower_cost = 100;
    array.free_towers = 3;
    return array;
}

int get_tower_cost(const TowerArray* array) {
    return array->free_towers ? 0: array->next_tower_cost;
} 

void add_free_towers(TowerArray* array, int nb_towers) {
    array->free_towers += nb_towers;
}

Error add_tower_array(TowerArray* array, Tower tower) {
    if (array->cur_len == MAX_TOWER) {
        return TOWER_ARRAY_FULL;
    }
    array->lst[array->cur_len] = tower;
    
    if (array->free_towers) {
        array->free_towers--;
    } else {
        array->next_tower_cost *= 2;
    }

    array->cur_len++;
    return OK;
}

void update_clock_tower(Tower* tower) {
    decrease_clock(&tower->deploy_timer);
    decrease_clock(&tower->shoot_interval);
}
