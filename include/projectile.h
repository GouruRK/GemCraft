#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "position.h"
#include "monster.h"
#include "gem.h"

typedef struct {
    float speed;
    Position pos;
    Monster* target;
    Gem source;
} Projectile;

typedef struct _node {
    struct _node* next;
    Projectile proj;
} *Node, ProjectileArray;

#endif
