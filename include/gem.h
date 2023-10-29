#ifndef GEM_H
#define GEM_H

typedef enum {  
    PYRO,
    DENDRO,
    HYDRO,
} TypeGems;

typedef struct {
    int level;
    int color;
    int reload_time;
    TypeGems type;
} Gem;

#endif
