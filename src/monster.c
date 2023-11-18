#include "../include/monster.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "position.h"
#include "util.h"

/**
 * @brief Initialize the monster health
 *
 * @param monster
 * @param wave_number
 */
static void init_monster_health(Monster* monster, int wave_number) {
    int h = 1000;
    monster->max_health = (int)(h * powf(1.2, wave_number));
    monster->health = monster->max_health;
}

/**
 * @brief Modify monster caracteristic if the monster is in specific wave
 *
 * @param monster
 * @param type_wave
 */
static void modify_monster_type(Monster* monster, TypeWave type_wave) {
    switch (type_wave) {
        case BOSS:
            monster->health *= 12;
            break;

        case FAST:
            monster->default_speed = 2;
            monster->speed = monster->default_speed;
            break;

        default:
            break;
    }
}

/**
 * @brief Set all monster status to NONE and set timers to 0
 *
 * @param monster
 */
static void init_all_monster_status(Monster* monster) {
    for (int i = 0; i < STACKABLE_STATUS; i++) {
        monster->status[i] = init_effect(NONE);
    }
}

Monster init_monster(Position pos_init, TypeWave type_wave, int wave_number,
                     Position dest) {
    Monster monster;

    init_monster_health(&monster, wave_number);

    monster.color = random_color();

    monster.pos = pos_init;
    monster.dest = dest;

    monster.index_path = 0;

    monster.default_speed = 1;
    monster.speed = monster.default_speed;

    init_all_monster_status(&monster);

    modify_monster_type(&monster, type_wave);

    return monster;
}

void move_monster(Monster* monster) {
    float direction = calc_direction(monster->pos, monster->dest);

    for (int i = 0; i < STACKABLE_STATUS; i++) {
        if (monster->status[i].status == SLOW) {
            monster->speed /= 1.5;
        }
        if (monster->status[i].status == SPRAYING) {
            monster->speed /= 1.25;
        }
        if (monster->status[i].status == PETRIFICUS) {
            return ;
        }
    }

    float fluctuation = uniform() * 0.2 + 0.9;
    float step = fluctuation * (monster->speed / FRAMERATE);

    monster->pos.x += cos(direction) * step;
    monster->pos.y += sin(direction) * step;
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

int is_alive(const Monster* monster) { return monster->health > 0; }

// All function to update monster effect
typedef void (*update_effect)(Monster* monster);

static void decrease_status_clock(Monster* monster) {
    for (int i = 0; i < STACKABLE_STATUS; i++) {
        decrease_clock(&monster->status[i].clock);
        if (monster->status->clock.remaining_time == 0) {
            monster->status[i] = init_effect(NONE);
        }
    }
}

static void update_parasit(Monster* monster) {
    if (monster->status->clock.next_interval == 0) {
        monster->health -= monster->status->next_damage;
    }
}

void update_effect_monster(Monster* monster) {
    static update_effect effect[] = {
        [PARASIT] = update_parasit,
    };

    if (monster->status->status == PARASIT) {
        effect[monster->status->status](monster);
    }
    decrease_status_clock(monster);
}

void add_effect_monster(Monster* monster, Effect effect) {
    for (int i = 0; i < STACKABLE_STATUS; i++) {
        if (monster->status[i].status == NONE) {
            monster->status[i] = effect;
        }
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
