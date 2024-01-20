#include "display/display_skill_tree.h"

#include <MLV/MLV_all.h>
#include <stdbool.h>

#include "user_event/skill_tree.h"
#include "game_engine/game.h"
#include "utils/sector.h"

#define PADDING_X 10
#define PADDING_Y 10

char* text[] = {
    [GIVE_MANA] = "Give %d mana",
    [FREE_TOWERS] = "Give %d free towers",
    [KILL_MONSTER] = "Kill %d monsters",
    [FREE_UPGRADE] = "Give free mana pool upgrade",
    [GIVE_GEM] = "Give pure gem of level %d"
};

/**
 * @brief Get space between each skill interface
 * 
 * @param window 
 * @return
 */
static int get_space_between(Sector window) {
    return window.width / (SKILLS_PROPOSAL + 1);
}

/**
 * @brief Get the sector for a certain skill at given offset
 * 
 * @param skill 
 * @param window 
 * @param x_offset 
 * @return
 */
static Sector get_sector_for_skills(Skill skill, Sector window, int x_offset) {
    static int init = 0, w, h;

    if (!init) {
        MLV_get_size_of_text(text[FREE_UPGRADE], &w, &h);
        init = 1;
    }

    int top_x = x_offset - get_space_between(window)/2;

    return init_sector(init_position(top_x, window.height/2 - h),
                       init_position(top_x + w + PADDING_X*2, 
                                     window.height/2 + h + PADDING_Y*2));
}

/**
 * @brief Initialise clickable sectors
 * 
 * @param tree 
 * @param window 
 */
void init_sectors(SkillTree* tree, Sector window) {
    int space_between = get_space_between(window);

    int x = 0;
    for (int i = 0; i < SKILLS_PROPOSAL; i++) {
        x = space_between + space_between*i;
        tree->sectors[i] = get_sector_for_skills(tree->skills[i], window, x);
    }

    tree->has_sectors = true;
}

void display_skill_tree(const Game* game) {
    MLV_draw_filled_rectangle(game->sectors.window.top_left.x,
                              game->sectors.window.top_left.y, 
                              game->sectors.window.width,
                              game->sectors.window.height,
                              MLV_rgba(51, 51, 51, 200));

    int x, y, w, h;

    for (int i = 0; i < SKILLS_PROPOSAL; i++) {
        MLV_draw_filled_rectangle(game->tree.sectors[i].top_left.x,
                                  game->tree.sectors[i].top_left.y,
                                  game->tree.sectors[i].width,
                                  game->tree.sectors[i].height,
                                  MLV_COLOR_WHITE);

        MLV_get_size_of_text(text[game->tree.skills[i]], &w, &h);

        x = game->tree.sectors[i].top_left.x + game->tree.sectors[i].width/2
                                             - w/4 - PADDING_X/2;
        y = game->tree.sectors[i].top_left.y + game->tree.sectors[i].height/2
                                             - h/2;

        if (game->tree.skills[i] == GIVE_MANA) {
            MLV_draw_text(x, y, "Give %d mana", MLV_COLOR_BLACK,
                          game->tree.give[i]);
        } else if (game->tree.skills[i] == FREE_TOWERS) {
            MLV_draw_text(x, y, "Give %d free towers", MLV_COLOR_BLACK,
                          game->tree.give[i]);
        } else if (game->tree.skills[i] == KILL_MONSTER) {
            MLV_draw_text(x, y, "Kill %d monsters", MLV_COLOR_BLACK,
                          game->tree.give[i]);
        } else if (game->tree.skills[i] == GIVE_GEM) {
            x = game->tree.sectors[i].top_left.x + 
                game->tree.sectors[i].width/2 - w/3;
            MLV_draw_text(x, y, "Give pure gem of level %d", MLV_COLOR_BLACK,
                          game->tree.give[i]);

        } else {
            x = game->tree.sectors[i].top_left.x +
                game->tree.sectors[i].width/2 - w/2;
            MLV_draw_text(x, y, "Give free mana pool upgrade", MLV_COLOR_BLACK,
                          game->tree.give[i]);   
        }
    }
}