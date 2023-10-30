#ifndef GEM_H
#define GEM_H

typedef enum {  
    PYRO,
    DENDRO,
    HYDRO,
    MIXTE
} TypeGems;

typedef struct {
    int level;
    int color;
    int reload_time;
    TypeGems type;
} Gem;

/**
 * @brief Creates a gem object.
 * 
 * @param type gem type
 * @param level gem level
 * @param color gem color
 * @return created gem
 */
Gem create_gem(TypeGems type, int level, int color);

Gem create_random_gem(int level);

#endif
