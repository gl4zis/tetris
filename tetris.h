#ifndef TETRIS_H
#define TETRIS_H

#include "stdbool.h"

#define BLOCK_NUM 4
#define POS_NUM 4
#define FIG_NUM 5
#define MAX_INT 99999
#define WIDTH 10
#define HEIGHT 20

// In blocks, not in pixels
typedef struct {
    int x;
    int y;
} Coord;

typedef struct {
    int width;
    int height;
} Size;

typedef struct {
    int idx;
    int pos;
    Coord coord;
} Figure;

typedef bool Field[HEIGHT][WIDTH];

typedef struct {
    int score;
    int dropped_num;
    Figure figure;
    Field field;
} Game;

typedef Coord Position[BLOCK_NUM];
typedef Position FPositions[POS_NUM];

extern const FPositions FIGURE_POSITIONS[FIG_NUM];

bool tick(Game* game);
Game init_game();

#endif //TETRIS_H
