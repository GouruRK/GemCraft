#include "game_engine/score.h"

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
