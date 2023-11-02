#include "../include/generation.h"

#include <stdlib.h>
#include <time.h>

#include "../include/field.h"
#include "../include/position.h"

#define PADDING 2  // Distance between elements

typedef enum { WEST, SOUTH, EAST, NORTH } Direction;

/**
 * @brief Give the oppostie direction of dir
 *
 * @param dir
 * @return Direction
 */
static Direction opposite_direction(Direction dir) { return (dir + 2) % 4; }

/**
 * @brief Check if a cell is isolated in a range of two cells
 *  Can ommit a check in a specified direction (-1 by default mean do not ignore
 * any direction)
 *
 * @param field
 * @param pos
 * @param ignore
 * @return int
 */
static int is_isolated(Field* field, Position pos, Direction ignore) {
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};

    for (int direction = 0; direction < 4; direction++) {
        if (direction != ignore) {
            for (int i = 1; i <= 2; i++) {
                Position check = {pos.x + i * dx[direction],
                                      pos.y + i * dy[direction]};

                if (check.x >= 0 && check.x < WIDTH && check.y >= 0 &&
                    check.y < HEIGHT) {
                    if (field->board[(int)check.y][(int)check.x] != EMPTY) {
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}

/**
 * @brief Set all the field's cells to EMPTY
 * 
 * @param field 
 */
static void empty_field(Field* field) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            field->board[y][x] = EMPTY;
        }
    }
}

/**
 * @brief Generate a nest with a space of minimum 2 cells from the edges of the field
 *
 * @param field
 */
static void generate_nest_pos(Field* field) {
    int x = (rand() % (WIDTH - PADDING * 2)) + PADDING;
    int y = (rand() % (HEIGHT - PADDING * 2)) + PADDING;

    field->board[y][x] = NEST;
    field->nest.x = x;
    field->nest.y = y;
}

/**
 * @brief Caclulate cardinal expanse for all directions from a
 * given position in the field
 * 
 * @param field 
 * @param pos 
 * @param card_expanse Calculated values
 */
static void calc_card_expanse(Field* field, Position pos,
                              int card_expanse[4]) {
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};

    for (int direction = 0; direction < 4; direction++) {
        Position check = pos;
        int count = 0;
        while ((field->board[(int)pos.y + dy[direction]][(int)check.x + dx[direction]] !=
                    PATH &&
                check.x > 0 && check.y > 0 && check.x < WIDTH - 1 &&
                check.y < HEIGHT - 1 &&
                is_isolated(field, check, opposite_direction(direction))) ||
               count < 1) {
            card_expanse[direction] += 1;
            check.x += dx[direction];
            check.y += dy[direction];
            count++;
        }

        card_expanse[direction] = (card_expanse[direction] <= PADDING)
                                      ? 0
                                      : card_expanse[direction] - PADDING;
    }
}

/**
 * @brief Choose randomly one direction using Weighted Random Selection
 * Should never return -1
 * By default, if the sum weight is equal to 0, resturn WEST
 * 
 * @param card_expanse 
 * @return Direction 
 */
static Direction choose_direction(int card_expanse[]) {
    int sum_weight = 0;
    for (int i = 0; i < 4; i++) {
        sum_weight += card_expanse[i];
    }

    if (sum_weight == 0) return WEST;

    int random = rand() % sum_weight;
    int combined = 0;
    for (int i = 0; i < 4; i++) {
        combined += card_expanse[i];
        if (combined >= random) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Genate a random number of cell to add in a direction following 
 * set between 3 and cardinal expanse
 * 
 * @param expanse 
 * @return int 
 */
static int nb_cell_to_add(int expanse) {
    int result = 0;
    for (int i = 0; i < expanse; i++) {
        if ((rand() % 4) != 0) {
            result++;
        }
    }
    return (result < 3) ? 3 : result;
}

/**
 * @brief Modify the field to add nb_cell PATH cells in the field from a given
 * position and direction
 * 
 * @param field 
 * @param dir 
 * @param nb_cell number of cells to add
 * @param pos 
 */
static void add_line(Field* field, Direction dir, int nb_cell,
                     Position* pos) {
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};

    for (int i = 0; i < nb_cell; i++) {
        pos->x += dx[dir];
        pos->y += dy[dir];

        field->monster_path.path[field->monster_path.cur_len].x = pos->x;
        field->monster_path.path[field->monster_path.cur_len].y = pos->y;
        field->monster_path.cur_len++;

        field->board[(int)pos->y][(int)pos->x] = PATH;
    }
}

/**
 * @brief Reset all value of expanse to 0
 * 
 * @param expanse 
 * @param len number of direction, in this project it is 4
 */
static void reset_expanse(int expanse[], int len) {
    for (int i = 0; i < len; i++) {
        expanse[i] = 0;
    }
}

Field generate_field() {
    Field field;
    int generation_over = 0;

    while (!generation_over) {
        int expanse[4] = {0, 0, 0, 0};
        int nb_turn = 0;
        field.monster_path.cur_len = 0;

        empty_field(&field);

        generate_nest_pos(&field);

        Position cur_position = field.nest;

        calc_card_expanse(&field, cur_position, expanse);

        Direction cur_dir = choose_direction(expanse);

        while (expanse[cur_dir] > 2) {
            int cells_to_add = nb_cell_to_add(expanse[cur_dir]);
            add_line(&field, cur_dir, cells_to_add, &cur_position);

            reset_expanse(expanse, 4);
            calc_card_expanse(&field, cur_position, expanse);
            if (cur_dir == NORTH || cur_dir == SOUTH) {
                expanse[NORTH] = 0;
                expanse[SOUTH] = 0;
                cur_dir = choose_direction(expanse);
            } else {
                expanse[EAST] = 0;
                expanse[WEST] = 0;
                cur_dir = choose_direction(expanse);
            }
            nb_turn++;
        }

        if (nb_turn >= 7 && field.monster_path.cur_len >= 75) {
            generation_over = 1;
        }
    }

    field.camp.x = (int)field.monster_path.path[field.monster_path.cur_len - 1].x;
    field.camp.y = (int)field.monster_path.path[field.monster_path.cur_len - 1].y;
    field.board[(int)field.monster_path.path[field.monster_path.cur_len - 1].y]
               [(int)field.monster_path.path[field.monster_path.cur_len - 1].x] =
        CAMP;
        
    return field;
}
