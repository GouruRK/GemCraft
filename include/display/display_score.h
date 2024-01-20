/**
 * @file display_score.h
 * @author Coserariu Alain & Kies Remy
 * @brief Display final image and score after loosing
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef DISPLAY_SCORE_H
#define DISPLAY_SCORE_H

#include "game_engine/score.h"
#include "display/game_sectors.h"

/**
 * @brief Display final score
 * 
 * @param score 
 * @param sectors 
 */
void display_score(Score* score, GameSectors* sectors);

#endif
