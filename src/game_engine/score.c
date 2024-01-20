#include "game_engine/score.h"

#include <math.h>

long compute_score(Score* score) {
    return score->boss_wave*10 + score->fast_wave*5 + score->crowd_wave*3
            + score->normal_wave + fmax(log10(score->total_damage), 0) 
            + score->monster_kills;
}

Score init_score(void) {
    Score score;
    score.boss_wave = 0;
    score.fast_wave = 0;
    score.crowd_wave = 0;
    score.normal_wave = 0;
    score.total_damage = 0;
    score.monster_kills = 0;
    return score;
}
