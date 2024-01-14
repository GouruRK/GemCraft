#include "user_event/skill_tree.h"

#include <stdbool.h>

#include "utils/util.h"

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

static void fill_values(SkillTree* tree, int wave) {
    for (int i = 0; i < SKILLS_PROPOSAL; i++) {
        switch (tree->skills[i]) {
            case GIVE_MANA:
                tree->give[i] = wave * 100;
                break;
            case KILL_MONSTER:
                tree->give[i] = wave % 10;
                break;
            case FREE_TOWERS:
                tree->give[i] = wave / 5;
                break;
            default:
                 tree->give[i] = 0;
                break;
        }
    }
}

SkillTree init_skill_tree(int wave) {
    SkillTree tree;
    fill_skills(&tree);
    fill_values(&tree, wave);
    tree.has_sectors = false;
    return tree;
}


