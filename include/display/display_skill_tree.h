#ifndef DISPLAY_SKILL_TREE_H
#define DISPLAY_SKILL_TREE_H

#include "user_event/skill_tree.h"
#include "game_engine/game.h"
#include "utils/sector.h"

/**
 * @brief Init sectors (or clickable sections for skill tree)
 * 
 * @param tree 
 * @param window 
 */
void init_sectors(SkillTree* tree, Sector window);

/**
 * @brief Display skill selector
 * 
 * @param game 
 */
void display_skill_tree(const Game* game);

#endif
