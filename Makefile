all: main.c tetris.c
	gcc -g -fsanitize=undefined -o tetris main.c tetris.c