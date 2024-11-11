#include "tetris.h"
#include <unistd.h>
#include <stdio.h>

void print_field(Game* game) {
    for (int y = 0; y < 20; y++) {
        printf("|");
        for (int x = 0; x < 10; x++) {
            bool printed = false;
            if (game->field[y][x]) {
                printf("#");
                printed = true;
            }
            for (int i = 0; i < BLOCK_NUM; i++) {
                Coord block = FIGURE_POSITIONS[game->figure.idx][game->figure.pos][i];
                int b_x = game->figure.coord.x + block.x;
                int b_y = game->figure.coord.y + block.y;
                if (x == b_x && y == b_y && !printed) {
                    printf("#");
                    printed = true;
                }
            }
            if (!printed) printf(" ");
        }
        printf("|\n");
    }
}

int main() {
    Game game = init_game();
    while (tick(&game)) {
        print_field(&game);
        usleep(300 * 1000);
    }
    print_field(&game);
    return 0;
}
