#include <stdbool.h>
#include <stdlib.h>

#include "game_engine/tower.h"
#include "game_engine/gem.h"
#include "utils/position.h"
#include "utils/errors.h"

Tower init_tower(Position pos) {
    Tower tower;
    tower.pos = pos;
    tower.hold_gem = false;
    return tower;
}

Error add_gem_to_tower(Tower* tower, Gem gem) {
    if (tower->hold_gem) {
        return NON_EMPTY_TOWER;
    }
    tower->gem = gem;
    tower->hold_gem = true;
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

// int main(void) {
//     TowerArray array = create_tower_array();
// 
//     for (int i = 0; i < 5; i++) {
//         printf("------------ Tower %d : ------------", i + 1);
//         add_tower_array(&array, init_tower((Gem){}, (Position){}));
//         printf("coast : %d\tcurlen : %d\n", array.next_tower_cost, array.cur_len);
//     }
// 
//     return 0;
// }
