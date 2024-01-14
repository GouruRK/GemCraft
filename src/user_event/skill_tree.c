#include "user_event/skill_tree.h"

#include <stdbool.h>
#include <math.h>

#include "utils/util.h"
#include "game_engine/player.h"

/**
 * @brief Give the amount of mana to be given at a certain wave
 * 
 * @param wave 
 * @return
 */
static inline int give_mana_value(Player* player, int wave) {
    return player->max_quantity/4;
}

/**
 * @brief Give the number of monsters to kill at a certain wave
 * 
 * @param wave 
 * @return
 */
static inline int give_monster_kill_value(Player* player, int wave) {
    return max(1, wave/6);
}

/**
 * @brief Give the number of free towers to give at a certain wave
 * 
 * @param wave 
 * @return
 */
static inline int give_free_towers_value(Player* player, int wave) {
    return !wave ? 1: sqrt(wave*1.5);
}

/**
 * @brief Do nothing
 * 
 * @param wave 
 * @return
 */
static inline int give_upgrade(Player* player, int wave) {
    return 0;
}

/**
 * @brief Give the level of the pure gem to be created at a certain wave
 * 
 * @param wave 
 * @return
 */
static inline int give_gem_level(Player* player, int wave) {
    return max(1, wave/4);
}

typedef int(*v_func)(Player*, int);

static v_func value_function[] = {
    [GIVE_MANA] = give_mana_value,
    [FREE_TOWERS] = give_free_towers_value,
    [KILL_MONSTER] = give_monster_kill_value,
    [FREE_UPGRADE] = give_upgrade,
    [GIVE_GEM] = give_gem_level
}; 

/**
 * @brief Find a skill to replace the one at replace_index
 * 
 * @param tree 
 * @param replace_index 
 * @return
 */
static Skill new_random_skill(SkillTree* tree, int replace_index) {
    bool valid = false;
    Skill skill;
    while (!valid) {
        valid = true;
        skill = random_int(0, NB_SKILLS - 1);
        for (int i = 0; i < NB_SKILLS; i++) {
            if (i != replace_index) {
                if (skill == tree->skills[i]) {
                    valid = false;
                }
            }
        }
    }
    return skill;
}

/**
 * @brief Fill skills on a new SkillTree structure
 * 
 * @param tree 
 */
static void fill_skills(SkillTree* tree) {
    int index = 0;
    Skill skill;
    while (index != SKILLS_PROPOSAL) {
        skill = random_int(0, NB_SKILLS - 1);
        int i;
        for (i = 0; i < index; i++) {
            if (tree->skills[i] == skill) {
                break;
            }
        }
        if (i == index) {
            tree->skills[i] = skill;
            index++;
        }
    }
}

/**
 * @brief Fill initials values for each skills
 * 
 * @param tree 
 * @param wave 
 */
static void fill_values(SkillTree* tree, Player* player, int wave) {
    for (int i = 0; i < SKILLS_PROPOSAL; i++) {
       tree->give[i] = value_function[tree->skills[i]](player, wave);
    }
}

SkillTree init_skill_tree(Player* player, int wave) {
    SkillTree tree;
    fill_skills(&tree);
    fill_values(&tree, player, wave);
    tree.has_sectors = false;
    tree.last_used_index = -1;
    return tree;
}

void replace_skill(SkillTree* tree, Player* player, int wave) {
    int index = tree->last_used_index;
    if (index == -1) {
        return;
    }
    tree->skills[index] = new_random_skill(tree, index);
    tree->give[index] = value_function[tree->skills[index]](player, wave);
}
