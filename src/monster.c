#include "../include/monster.h"

#include <game.h>
#include <math.h>
#include <stdlib.h>

#include "../include/position.h"
#include "../include/util.h"

Monster init_monster(Position pos_init, TypeWave type_wave, int wave_number,
                     Position dest) {
    Monster monster;

    int h = 100;

    monster.max_health = (int)(h * powf(1.2, wave_number));
    monster.health = monster.max_health;
    monster.color = random_int(0, 359);

    monster.pos.x = pos_init.x + 0.5;
    monster.pos.y = pos_init.y + 0.5;

    monster.dest.x = dest.x + 0.5;
    monster.dest.y = dest.y + 0.5;

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
