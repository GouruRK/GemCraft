#ifndef DISPLAY_SKILL_TREE_H
#define DISPLAY_SKILL_TREE_H

#include "user_event/skill_tree.h"
#include "game_engine/game.h"
#include "utils/sector.h"

void init_sectors(SkillTree* tree, Sector window);
void display_skill_tree(const Game* game);

#endif
