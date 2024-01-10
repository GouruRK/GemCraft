#ifndef SCORE_H
#define SCORE_H

typedef struct {
    int boss_wave;
    int fast_wave;
    int crowd_wave;
    int normal_wave;
    long total_damage;
    int monster_kills; 
} Score;

/**
 * @brief Initiate default scores
 * 
 * @return
 */
Score init_score(void);

#endif
