#include "../include/monster.h"

#include <game.h>
#include <math.h>
#include <stdlib.h>

#include "../include/position.h"
#include "../include/util.h"

#define FLOAT_COMPARISON_MARGIN 0.01

Monster init_monster(Position pos_init, TypeWave type_wave, int wave_number,
                     Position dest) {
    Monster monster;

    int h = 100;

    monster.max_health = (int)(h * powf(1.2, wave_number));
    monster.health = monster.max_health;
    monster.color = random_int(0, 359);

    monster.pos = pos_init; 
    monster.dest = dest;

    monster.index_path = 0;

    monster.speed = 1;
    monster.status = NONE;

    monster.effect_duration.tv_nsec = 0;
    monster.effect_duration.tv_sec = 0;

    switch (type_wave) {
        case NORMAL:
            monster.health *= 12;
            break;

        case FAST:
            monster.speed = 2;
            break;

        default:
            break;
    }

    return monster;
}

void move_monster(Monster* monster) {
    float direction = calc_direction(monster->pos, monster->dest);

    monster->pos.x += cos(direction) * (monster->speed / FRAMERATE);
    monster->pos.y += sin(direction) * (monster->speed / FRAMERATE);
}

int has_reach_dest(Monster* monster) {
    if (monster->dest.x - FLOAT_COMPARISON_MARGIN < monster->pos.x &&
        monster->pos.x < monster->dest.x + FLOAT_COMPARISON_MARGIN &&
        monster->dest.y - FLOAT_COMPARISON_MARGIN < monster->pos.y &&
        monster->pos.y < monster->dest.y + FLOAT_COMPARISON_MARGIN) {
        return 1;
    }

    return 0;
}

/*---------------------------Monster array related---------------------------*/

Error init_monster_array(MonsterArray* array) {
    array->curr_size = 0;
    array->max_size = MAX_WAVE_SIZE;
    array->lst = (Monster*)malloc(MAX_WAVE_SIZE * sizeof(Monster));
    if (!array->lst) {
        return ALLOCATION_ERROR;
    }

    return OK;
}

Error realloc_monster_array(MonsterArray* array) {
    if (array->curr_size == array->max_size) {
        array->lst = (Monster*)realloc(
            array->lst, sizeof(Monster) * (array->max_size + MAX_WAVE_SIZE));
        if (!array->lst) {
            return ALLOCATION_ERROR;
        }
        array->max_size += MAX_WAVE_SIZE;

        return OK;
    } else if (array->curr_size <= array->max_size - MAX_WAVE_SIZE) {
        array->lst = (Monster*)realloc(
            array->lst, sizeof(Monster) * (array->max_size - MAX_WAVE_SIZE));
        if (!array->lst) {
            return ALLOCATION_ERROR;
        }
        array->max_size -= MAX_WAVE_SIZE;

        return OK;
    }

    return INCOHERENT_ARRAY_DATA;
}

Error add_monster_array(MonsterArray* array, Monster monster) {
    if (array->curr_size == array->max_size) {
        Error error = realloc_monster_array(array);
        if (error != OK) {
            return error;
        }
    }

    array->lst[array->curr_size] = monster;
    array->curr_size++;

    return OK;
}
