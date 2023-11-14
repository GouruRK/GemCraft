#include "projectile.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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
    proj->target->status = SPRAYING;
    for (int i = 0; i < array->curr_size; i++) {
        float dist_proj_monster = calc_distance(proj->pos, array->lst[i].pos);
        if (is_alive(&array->lst[i]) && dist_proj_monster < 3.5) {
            if (array->lst[i].status == NONE) {
                array->lst[i].status = SPRAYING;
            }
            array->lst[i].health -= (5 * hit_damage(proj) / 100);
            array->lst[i].speed /= 1.25;
            array->lst[i].effect_duration = FRAMERATE * 5;
        }
    }
}

static void apply_pyro_dendro(Projectile* proj) {
    proj->target->health -= hit_damage(proj) * 2;
    proj->target->status = NONE;
}

static void apply_hydro_dendro(Projectile* proj) {
    proj->target->status = PETRIFICUS;
    proj->target->effect_duration = FRAMERATE * 3;
    proj->target->speed = 0;
}

static void apply_pyro(MonsterArray* array, Projectile* proj) {
    if (proj->target->status == PYRO_RESIDUE) {
        for (int i = 0; i < array->curr_size; i++) {
            if (is_alive(&array->lst[i]) && &array->lst[i] != proj->target &&
                calc_distance(proj->pos, array->lst[i].pos) < 2) {
                array->lst[i].health -= (15 * hit_damage(proj) / 100);
            }
        }
        proj->target->status = NONE;
    } else if (proj->target->status == HYDRO_RESIDUE) {
        apply_pyro_hydro(array, proj);
    } else if (proj->target->status == DENDRO_RESIDUE) {
        apply_pyro_dendro(proj);
    } else if (proj->target->status == NONE) {
        proj->target->status = PYRO_RESIDUE;
    }
}

static void apply_dendro(MonsterArray* array, Projectile* proj) {
    if (proj->target->status == DENDRO_RESIDUE ||
        proj->target->status == PARASIT) {
        proj->target->status = PARASIT;
        proj->target->damage_timer = FRAMERATE / 2;
        proj->target->next_damage = 2.5 * hit_damage(proj) / 100;
        proj->target->frame_before_next_damage = proj->target->damage_timer;
        proj->target->effect_duration = FRAMERATE * 10;
    } else if (proj->target->status == PYRO_RESIDUE) {
        apply_pyro_dendro(proj);
    } else if (proj->target->status == HYDRO_RESIDUE) {
        apply_hydro_dendro(proj);
    } else if (proj->target->status == NONE) {
        proj->target->status = DENDRO_RESIDUE;
    }
}

static void apply_hydro(MonsterArray* array, Projectile* proj) {
    if (proj->target->status == HYDRO_RESIDUE || proj->target->status == SLOW) {
        proj->target->status = SLOW;
        proj->target->speed /= 1.5;
        proj->target->effect_duration = FRAMERATE * 10;
    } else if (proj->target->status == PYRO_RESIDUE) {
        apply_pyro_hydro(array, proj);
    } else if (proj->target->status == DENDRO_RESIDUE) {
        apply_hydro_dendro(proj);
    } else if (proj->target->status == NONE) {
        proj->target->status = HYDRO_RESIDUE;
    }
}

void hit_target(Projectile* proj, MonsterArray* array) {
    static apply_effect apply[] = {
        [PYRO] = apply_pyro,
        [DENDRO] = apply_dendro,
        [HYDRO] = apply_hydro,
    };
    apply[proj->source.type](array, proj);
    proj->target->health -= hit_damage(proj);
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
