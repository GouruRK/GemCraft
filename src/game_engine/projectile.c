#include "game_engine/projectile.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "game_engine/effect.h"
#include "game_engine/game.h"
#include "utils/position.h"

/*-----------------------------Projectile related-----------------------------*/

Projectile init_projectile(Position pos, Monster* target, Gem source) {
    Projectile proj;
    proj.pos = pos;
    proj.target = target;
    proj.source = source;
    proj.speed = 3;  // default speed at 3 tiles per seconds
    return proj;
}

/**
 * @brief Return the damage produce by a projectile on an enemy
 *
 * @param proj
 * @return int
 */
static int hit_damage(const Projectile* proj) {
    int d = 37;
    double diff_color = degree_to_rad(proj->source.color) - 
                        degree_to_rad(proj->target->color);
    int damage = (d * (1 << proj->source.level) * (1 - cos(diff_color) / 2));
    
    if (proj->source.type == MIXTE) {
        if (random_int(0, 10) == 0) damage *= 2;
        return damage * 2;
    }

    return damage;
}

/**
 * @brief Calculate the direction vector toward the target
 *
 * @param proj
 * @return Position
 */
static Position direction_proj(Projectile* proj) {
    Position vector;
    float dist_proj_target = calc_distance(proj->pos, proj->target->pos);
    vector.x = (proj->target->pos.x - proj->pos.x) / (dist_proj_target);
    vector.y = (proj->target->pos.y - proj->pos.y) / (dist_proj_target);
    return vector;
}

int has_reach_target(Projectile* proj) {
    if (calc_distance(proj->pos, proj->target->pos) < proj->speed / FRAMERATE) {
        return 1;
    }

    return 0;
}

/* Functions to apply status to the target */
typedef void (*apply_effect)(MonsterArray* array, Score* score, 
                             Projectile* proj, Player* player);

static void apply_pyro_hydro(MonsterArray* array, Score* score, 
                             Projectile* proj, Player* player) {
    Monster* tmp = proj->target;
    
    for (int i = 0; i < array->array_size; i++) {
        float dist_proj_monster = calc_distance(proj->pos, array->array[i].pos);
        
        if (is_alive(&array->array[i]) && dist_proj_monster <= 3.5) {
            proj->target = &array->array[i];
            
            add_effect_monster(&array->array[i], init_effect(SPRAYING, 0));
            take_damage(&(array->array[i]), score, hit_damage(proj) * 0.05);

            if (!is_alive(&(array->array[i])) && (tmp != &(array->array[i]))) {
                int mana_drop = array->array[i].max_health * 0.1 *
                                pow(1.3, player->mana_lvl);
                player->mana =
                    min(player->max_quantity, mana_drop + player->mana);
            }
        }
    }

    proj->target = tmp;
}

static void apply_pyro_dendro(Projectile* proj, Score* score) {
    take_damage(proj->target, score, hit_damage(proj) * 2);
}

static void apply_hydro_dendro(Projectile* proj) {
    add_effect_monster(proj->target, init_effect(PETRIFICUS, 0));
}

static void apply_pyro(MonsterArray* array, Score* score, Projectile* proj, 
                       Player* player) {
    if (proj->target->residue == PYRO_RESIDUE) {
        // Give 15% of base damage to monsters within 2 tiles
        Monster* tmp = proj->target;

        for (int i = 0; i < array->array_size; i++) {
            if (is_alive(&array->array[i]) &&
                calc_distance(proj->pos, array->array[i].pos) < 2) {
                
                // Change target to hit 15% damage on other monsters
                proj->target = &array->array[i];
                take_damage(&(array->array[i]), score, hit_damage(proj) * 0.15);

                if (!is_alive(&(array->array[i])) && 
                    (tmp != &(array->array[i]))) {
                int mana_drop = array->array[i].max_health * 0.1 *
                                pow(1.3, player->mana_lvl);
                player->mana =
                    min(player->max_quantity, mana_drop + player->mana);
            }
            }
        }
        proj->target = tmp;

    } else if (proj->target->residue == HYDRO_RESIDUE) {
        apply_pyro_hydro(array, score, proj, player);
        proj->target->residue = NONE;
    } else if (proj->target->residue == DENDRO_RESIDUE) {
        apply_pyro_dendro(proj, score);
        proj->target->residue = NONE;
    } else if (proj->target->residue == NONE) {
        proj->target->residue = PYRO_RESIDUE;
    }
}

static void apply_dendro(MonsterArray* array, Score* score, Projectile* proj, 
                         Player* player) {
    if (proj->target->residue == DENDRO_RESIDUE && 
        proj->target->status[0].status == PARASIT) {
        proj->target->status[0].clock.remaining_time = 10 * FRAMERATE;
        proj->target->status[0].next_damage = hit_damage(proj) * 0.025;
    } else if (proj->target->residue == DENDRO_RESIDUE) {
        add_effect_monster(proj->target, 
                           init_effect(PARASIT, hit_damage(proj) * 0.025));
    } else if (proj->target->residue == PYRO_RESIDUE) {
        apply_pyro_dendro(proj, score);
        proj->target->residue = NONE;
    } else if (proj->target->residue == HYDRO_RESIDUE) {
        apply_hydro_dendro(proj);
        proj->target->residue = NONE;
    } else if (proj->target->residue == NONE) {
        proj->target->residue = DENDRO_RESIDUE;
    }
}

static void apply_hydro(MonsterArray* array, Score* score, Projectile* proj, 
                        Player* player) {
    if (proj->target->residue == HYDRO_RESIDUE) {
        add_effect_monster(proj->target, init_effect(SLOW, 0));
    } else if (proj->target->residue == PYRO_RESIDUE) {
        apply_pyro_hydro(array, score, proj, player);
        proj->target->residue = NONE;
    } else if (proj->target->residue == DENDRO_RESIDUE) {
        apply_hydro_dendro(proj);
        proj->target->residue = NONE;
    } else if (proj->target->residue == NONE) {
        proj->target->residue = HYDRO_RESIDUE;
    }
}

void hit_target(Projectile* proj, Score* score, MonsterArray* array,
                Player* player) {
    static apply_effect apply[] = {
        [PYRO] = apply_pyro,
        [DENDRO] = apply_dendro,
        [HYDRO] = apply_hydro,
    };

    take_damage(proj->target, score, hit_damage(proj));
    if (proj->source.type != MIXTE) {
        apply[proj->source.type](array, score, proj, player);
    }
}

void move_projectile(Projectile* proj) {
    Position vector_direction = direction_proj(proj);

    proj->pos.x += vector_direction.x * proj->speed / FRAMERATE;
    proj->pos.y += vector_direction.y * proj->speed / FRAMERATE;
}

/*--------------------------------List Related--------------------------------*/

Error init_projectile_array(ProjectileArray* array) {
    array->array =
        (Projectile*)malloc(sizeof(Projectile) * BASE_PROJ_ARRAY_SIZE);
    if (!array->array) return ALLOCATION_ERROR;

    array->max_size = BASE_PROJ_ARRAY_SIZE;
    array->nb_elt = 0;

    return OK;
}

/**
 * @brief Double max_size of the array
 *
 * @param array
 * @return Error ALLOCATION_ERROR
 */
static Error realloc_projectile_array(ProjectileArray* array) {
    Projectile* tmp =
        realloc(array->array, (array->max_size * 2) * sizeof(Projectile));
    if (!tmp) {
        return ALLOCATION_ERROR;
    }

    array->array = tmp;
    array->max_size *= 2;
    return OK;
}

Error add_projectile_array(ProjectileArray* array, Projectile proj) {
    if (array->nb_elt == array->max_size) {
        if (realloc_projectile_array(array) == ALLOCATION_ERROR) {
            return ALLOCATION_ERROR;
        }
    }

    array->array[array->nb_elt] = proj;
    array->nb_elt++;

    return OK;
}

void suppress_proj_index(ProjectileArray* array, int index) {
    if (index >= array->nb_elt || index < 0) {
        return;
    }

    if (index != array->nb_elt - 1) {
        array->array[index] = array->array[array->nb_elt - 1];
    }
    array->nb_elt--;

}
