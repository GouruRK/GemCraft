#include "projectile.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "effect.h"
#include "game.h"
#include "position.h"

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
        for (int i = 0; i < array->array_size; i++) {
            if (is_alive(&array->array[i]) &&
                calc_distance(proj->pos, array->array[i].pos) < 2) {
                proj->target = &array->array[i];
                array->array[i].health -= (15 * hit_damage(proj) / 100);
            }
        }
        proj->target->status[0].status = NONE;
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

Node* init_node(void) { return (Node*)malloc(sizeof(Node)); }

Node* init_filled_node(Projectile proj) {
    Node* node = init_node();
    if (node) {
        node->proj = proj;
        node->next = NULL;
    }
    return node;
}

ProjectileArray init_array(void) { return NULL; }

int add_node(ProjectileArray* array, Node* node) {
    if (!node) return 0;

    node->next = *array;
    *array = node;

    return 1;
}

int add_projectile(ProjectileArray* array, Projectile proj) {
    return add_node(array, init_filled_node(proj));
}

Node* pop_node(ProjectileArray* array) {
    if (!(*array)) return NULL;

    Node* node = *array;
    *array = (*array)->next;

    return node;
}

void free_array(ProjectileArray* array) {
    Node* temp;
    while (*array) {
        temp = (*array)->next;
        free(*array);
        *array = temp;
    }
}

// Test allocation and free
// int main(void) {
//     ProjectileArray array = init_array();
//     add_projectile(&array, init_projectile((Position){}, NULL, (Gem){}));
//     add_projectile(&array, init_projectile((Position){}, NULL, (Gem){}));
//     add_projectile(&array, init_projectile((Position){}, NULL, (Gem){}));
//     free_array(&array);
// }
