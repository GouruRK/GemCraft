#ifndef SKILL_TREE_H
#define SKILL_TREE_H

#include <stdbool.h>

#include "utils/sector.h"
#include "game_engine/player.h"

#define WAVE_OFFSET 6
#define NB_SKILLS 5
#define SKILLS_PROPOSAL 3


typedef enum {
    GIVE_MANA,
    FREE_TOWERS,
    KILL_MONSTER,
    FREE_UPGRADE,
    GIVE_GEM,
} Skill;

typedef struct {
    bool has_sectors;
    int last_used_index;
    Skill skills[SKILLS_PROPOSAL];
    int give[SKILLS_PROPOSAL];
    Sector sectors[SKILLS_PROPOSAL];
} SkillTree;

/**
 * @brief Initialise the skill tree structure
 * 
 * @param wave 
 * @return
 */
SkillTree init_skill_tree(Player* player, int wave);

/**
 * @brief Replace skill at given index
 * 
 * @param tree 
 * @param index 
 * @param wave 
 */
void replace_skill(SkillTree* tree, Player* player, int wave);

#endif
