#include "display/display_score.h"

#include <MLV/MLV_all.h>

#include "game_engine/score.h"
#include "display/game_sectors.h"

/**
 * @brief Calculate the final score
 * 
 * @param score 
 * @return
 */
static long compute_score(Score* score) {
    return score->boss_wave*10  + score->fast_wave*5 + score->crowd_wave*3
            + score->normal_wave + score->total_damage/10 
            + score->monster_kills;
}

void display_score(Score* score, GameSectors* sectors) {
    MLV_draw_filled_rectangle(sectors->window.top_left.x,
                              sectors->window.top_left.y,
                              sectors->window.width,
                              sectors->window.height,
                              MLV_rgba(255, 255, 255, 175));

    int text_x = sectors->window.width/4;
    int score_x = sectors->window.width*3/4;

    int text_height = 20;
    int top_y = sectors->window.height/2 - (text_height*7)/2; // 7 because there
                                                              // are 7 lines of
                                                              // text
    // boss waves
    MLV_draw_text(text_x, top_y, "Boss Waves", MLV_COLOR_BLACK);
    MLV_draw_text(score_x, top_y, "%d", MLV_COLOR_BLACK, score->boss_wave);

    // fast wave
    MLV_draw_text(text_x, top_y + text_height, "Fast Waves", MLV_COLOR_BLACK);
    MLV_draw_text(score_x, top_y + text_height, "%d", MLV_COLOR_BLACK,
                  score->fast_wave);

    // crowd wave
    MLV_draw_text(text_x, top_y + text_height*2, "Crowd Waves",
                  MLV_COLOR_BLACK);
    MLV_draw_text(score_x, top_y + text_height*2, "%d", MLV_COLOR_BLACK,
                  score->crowd_wave);

    // crowd wave
    MLV_draw_text(text_x, top_y + text_height*3, "Normal Waves",
                  MLV_COLOR_BLACK);
    MLV_draw_text(score_x, top_y + text_height*3, "%d", MLV_COLOR_BLACK,
                  score->normal_wave);

    // kills
    MLV_draw_text(text_x, top_y + text_height*4, "Monster killed",
                  MLV_COLOR_BLACK);
    MLV_draw_text(score_x, top_y + text_height*4, "%d", MLV_COLOR_BLACK,
                  score->monster_kills);

    // total damage
    MLV_draw_text(text_x, top_y + text_height*5, "Total Damages",
                  MLV_COLOR_BLACK);
    MLV_draw_text(score_x, top_y + text_height*5, "%ld", MLV_COLOR_BLACK,
                  score->total_damage);

    // Total Score 
    MLV_draw_text(text_x, top_y + text_height*6, "Final Score",
                  MLV_COLOR_BLACK);
    MLV_draw_text(score_x, top_y + text_height*6, "%ld", MLV_COLOR_BLACK,
                  compute_score(score));
}
