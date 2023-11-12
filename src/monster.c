#include "../include/monster.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "game.h"
#include "position.h"
#include "util.h"

Monster init_monster(Position pos_init, TypeWave type_wave, int wave_number,
                     Position dest) {
    Monster monster;

    int h = 1000;

    monster.max_health = (int)(h * powf(1.2, wave_number));
    monster.health = monster.max_health;
    monster.color = random_color();

    monster.pos = pos_init; 
    monster.dest = dest;

    monster.index_path = 0;

    monster.default_speed = 1;
    monster.speed = monster.default_speed;
    monster.status = NONE;

    monster.effect_duration = 0;
    monster.damage_timer = 0;
    monster.next_damage = 0;

    switch (type_wave) {
        case BOSS:
            monster.health *= 12;
            break;

        case FAST:
            monster.default_speed = 2;
            monster.speed = monster.default_speed;
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

int has_reach_dest(const Monster* monster) {
    if (monster->dest.x - FLOAT_COMPARISON_MARGIN < monster->pos.x &&
        monster->pos.x < monster->dest.x + FLOAT_COMPARISON_MARGIN &&
        monster->dest.y - FLOAT_COMPARISON_MARGIN < monster->pos.y &&
        monster->pos.y < monster->dest.y + FLOAT_COMPARISON_MARGIN) {
        return 1;
    }

    return 0;
}

int is_alive(const Monster* monster) {
    return monster->health > 0;
}

// All function to update monster effect

static void reset_status(Monster* monster) {
    monster->status = NONE;
    monster->damage_timer = 0;
    fprintf(stderr, "coucou, %f\n", monster->speed);
    monster->speed = monster->default_speed;
    fprintf(stderr, "coucou, %f\n", monster->speed);
    monster->effect_duration = 0;
    monster->frame_before_next_damage = 0;
    monster->next_damage = 0;
}

void update_parasit_effect(Monster* monster) {
    if (monster->frame_before_next_damage == 0) {
        monster->health -= monster->next_damage;
        monster->frame_before_next_damage = monster->damage_timer;
    }
    
    monster->effect_duration--;
    monster->frame_before_next_damage--;

    if (monster->effect_duration == 0) {
        reset_status(monster);
    }
}

void update_slow_effect(Monster* monster) {
    monster->effect_duration--;

    if (monster->effect_duration == 0) {
        reset_status(monster);
    }
}

void update_spraying_effect(Monster* monster) {
    monster->effect_duration--;

    if (monster->effect_duration == 0) {
        reset_status(monster);
    }
}

void update_petrificus_effect(Monster* monster) {
    monster->effect_duration--;

    if (monster->effect_duration == 0) {
        reset_status(monster);
    }
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
