#include "tetris.h"
#include <stdlib.h>
#include <stdio.h>

const FPositions FIGURE_POSITIONS[FIG_NUM] = {
        {
            {{0, 0}, {0, 1}, {1, 1}, {1, 0}},
            {{0, 0}, {0, 1}, {1, 1}, {1, 0}},
            {{0, 0}, {0, 1}, {1, 1}, {1, 0}},
            {{0, 0}, {0, 1}, {1, 1}, {1, 0}}
        }, // square
        {
            {{0, 0}, {0, 1}, {0, 2}, {0, 3}},
            {{0, 0}, {1, 0}, {2, 0}, {3, 0}},
            {{0, 0}, {0, 1}, {0, 2}, {0, 3}},
            {{0, 0}, {1, 0}, {2, 0}, {3, 0}}
        }, // |
        {
            {{0, 0}, {1, 0}, {2, 0}, {1, 1}},
            {{0, 1}, {1, 0}, {1, 1}, {1, 2}},
            {{1, 0}, {0, 1}, {1, 1}, {2, 1}},
            {{0, 0}, {0, 1}, {0, 2}, {1, 1}}
        }, // T
        {
            {{0, 0}, {0, 1}, {0, 2}, {1, 2}},
            {{0, 0}, {0, 1}, {1, 0}, {2, 0}},
            {{0, 0}, {1, 0}, {1, 1}, {1, 2}},
            {{2, 0}, {0, 1}, {1, 1}, {2, 1}}
        }, // L
        {
            {{0, 0}, {1, 0}, {1, 1}, {2, 1}},
            {{1, 0}, {1, 1}, {0, 1}, {0, 2}},
            {{0, 0}, {1, 0}, {1, 1}, {2, 1}},
            {{1, 0}, {1, 1}, {0, 1}, {0, 2}}
        } // Z за наших
};

Size get_f_size(int idx, int pos) {
    int min_x = MAX_INT;
    int min_y = MAX_INT;
    int max_x = 0;
    int max_y = 0;
    for (int i = 0; i < BLOCK_NUM; i++) {
        Coord coord = FIGURE_POSITIONS[idx][pos][i];
        if (coord.x < min_x) min_x = coord.x;
        if (coord.x > max_x) max_x = coord.x;
        if (coord.y < min_y) min_y = coord.y;
        if (coord.y > max_y) max_y = coord.y;
    }
    return (Size) {(max_x - min_x + 1), (max_y - min_y + 1)};
}

Figure init_figure() {
    int idx = rand() % 5;
    int pos = rand() % 4;
    Size f_size = get_f_size(idx, pos);
    int x = rand() % (WIDTH - f_size.width);
    return (Figure) {idx, pos, {x, 0}};
}

Game init_game() {
    Figure fig = init_figure();
    return (Game) {
        .score = 0,
        .dropped_num = 0,
        .figure = fig,
        .field = {0}
    };
}

bool fallen(Game* game) {
    for (int i = 0; i < BLOCK_NUM; i++) {
        Coord block = FIGURE_POSITIONS[game->figure.idx][game->figure.pos][i];
        int x = game->figure.coord.x + block.x;
        int y = game->figure.coord.y + block.y;
        if (y + 1 == HEIGHT) return true;
        if (game->field[y + 1][x]) return true;
    }
    return false;
}

bool valid_f_coords(Game* game) {
    for (int i = 0; i < BLOCK_NUM; i++) {
        Coord block = FIGURE_POSITIONS[game->figure.idx][game->figure.pos][i];
        int x = game->figure.coord.x + block.x;
        int y = game->figure.coord.y + block.y;
        if (x < 0 || y < 0) return false;
        if (x >= WIDTH || y >= HEIGHT) return false;
        if (game->field[y][x]) return false;
    }
    return true;
}

void add_figure_to_field(Game* game) {
    for (int i = 0; i < BLOCK_NUM; i++) {
        Coord block = FIGURE_POSITIONS[game->figure.idx][game->figure.pos][i];
        int x = game->figure.coord.x + block.x;
        int y = game->figure.coord.y + block.y;
        game->field[y][x] = true;
    }
}

bool loosed(Game* game) {
    if (!valid_f_coords(game)) return true;
    for (int i = 0; i < WIDTH; i++) {
        if (game->field[0][i]) return true;
    }
    return false;
}

bool tick(Game* game) {
    game->figure.coord.y++;
    if (fallen(game)) {
        add_figure_to_field(game);
        game->dropped_num++;
        game->figure = init_figure();
    }
    return !loosed(game);
}