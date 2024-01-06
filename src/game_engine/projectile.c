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
    int d = 100;
    return (int)(d * (2 << proj->source.level) *
                 (1 - cosf(proj->source.color - proj->target->color) / 2));
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
typedef void (*apply_effect)(MonsterArray* array, Projectile* proj);

static void apply_pyro_hydro(MonsterArray* array, Projectile* proj) {
    Monster* tmp = proj->target;

    proj->target->status[1].status = SPRAYING;
    proj->target->status[0].status = NONE;
    for (int i = 0; i < array->array_size; i++) {
        float dist_proj_monster = calc_distance(proj->pos, array->array[i].pos);
        if (is_alive(&array->array[i]) && dist_proj_monster < 3.5) {
            proj->target = &array->array[i];
            array->array[i].status[1].status = SPRAYING;
            array->array[i].health -= (5 * hit_damage(proj) / 100);
            array->array[i].status[1].clock = init_clock(-1, 5);
        }
    }

    proj->target = tmp;
}

static void apply_pyro_dendro(Projectile* proj) {
    proj->target->health -= hit_damage(proj) * 2;
    proj->target->status[0].status = NONE;
}

static void apply_hydro_dendro(Projectile* proj) {
    proj->target->status[0].status = PETRIFICUS;
    proj->target->status[0].clock = init_clock(-1, 3);
}

static void apply_pyro(MonsterArray* array, Projectile* proj) {
    if (proj->target->status[0].status == PYRO_RESIDUE) {
        Monster* tmp = proj->target;
        for (int i = 0; i < array->array_size; i++) {
            if (is_alive(&array->array[i]) &&
                calc_distance(proj->pos, array->array[i].pos) < 2) {
                proj->target = &array->array[i];
                array->array[i].health -= (15 * hit_damage(proj) / 100);
            }
        }
        proj->target->status[0].status = NONE;
        proj->target = tmp;
    } else if (proj->target->status[0].status == HYDRO_RESIDUE) {
        apply_pyro_hydro(array, proj);
    } else if (proj->target->status[0].status == DENDRO_RESIDUE) {
        apply_pyro_dendro(proj);
    } else if (proj->target->status[0].status == NONE) {
        proj->target->status[0].status = PYRO_RESIDUE;
    }
}

static void apply_dendro(MonsterArray* array, Projectile* proj) {
    if (proj->target->status[0].status == DENDRO_RESIDUE ||
        proj->target->status[0].status == PARASIT) {
        proj->target->status[0].status = PARASIT;
        proj->target->status[0].clock = init_clock(0.5, 10);
        proj->target->status[0].next_damage = 2.5 * hit_damage(proj) / 100;
    } else if (proj->target->status[0].status == PYRO_RESIDUE) {
        apply_pyro_dendro(proj);
    } else if (proj->target->status[0].status == HYDRO_RESIDUE) {
        apply_hydro_dendro(proj);
    } else if (proj->target->status[0].status == NONE) {
        proj->target->status[0].status = DENDRO_RESIDUE;
    }
}

static void apply_hydro(MonsterArray* array, Projectile* proj) {
    if (proj->target->status[0].status == HYDRO_RESIDUE ||
        proj->target->status[0].status == SLOW) {
        proj->target->status[0].status = SLOW;
        proj->target->status[0].clock = init_clock(-1, 10);
    } else if (proj->target->status[0].status == PYRO_RESIDUE) {
        apply_pyro_hydro(array, proj);
    } else if (proj->target->status[0].status == DENDRO_RESIDUE) {
        apply_hydro_dendro(proj);
    } else if (proj->target->status[0].status == NONE) {
        proj->target->status[0].status = HYDRO_RESIDUE;
    }
}

void hit_target(Projectile* proj, MonsterArray* array) {
    proj->target->health -= hit_damage(proj);
    static apply_effect apply[] = {
        [PYRO] = apply_pyro,
        [DENDRO] = apply_dendro,
        [HYDRO] = apply_hydro,
    };
    if (proj->source.type != MIXTE) {
        apply[proj->source.type](array, proj);
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
