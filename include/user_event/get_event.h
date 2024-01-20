/**
 * @file get_event.h
 * @author Coserariu Alain & Kies Remy
 * @brief Contains functions to get the current user event
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef GET_EVENT_H
#define GET_EVENT_H

#include "event.h"
#include "interact.h"
#include "display/game_sectors.h"

/**
 * @brief Get the current event
 * 
 * @param interaction current player interaction
 * @return current event
 */
Event get_event(Interaction interaction, const GameSectors* sectors);

/**
 * @brief Get event while game status is on SKILLS
 * 
 * @param tree skills tree selector
 * @return
 */
Event get_skill_event(SkillTree* tree);

#endif
