#ifndef GEM_H
#define GEM_H

typedef enum {    // Get evolution with `gem_A | gem_B`
    PYRO = 1,     // 0b001
    DENDRO,       // 0b010
    PYRO_DENDRO,  // 0b011
    HYDRO,        // 0b100
    PYRO_HYDRO,   // 0b101
    DENDRO_HYDRO, // 0b110
} TypeGems;

typedef enum {
    SPLASH,         // Pyro
    PARASIT,        // Dendro
    SLOW,           // Hydro
    SPRAYING,       // Pyro + Hydro
    BURN,           // Pyro + Dendro
    PETRIFICUS,     // Dendro + Hydro
} Effect;

typedef struct {
    int level;
    int color;
    TypeGems type;
    Effect effect;
} Gem;

#endif
