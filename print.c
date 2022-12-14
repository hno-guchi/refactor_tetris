#include <ncurses.h>
#include "game.h"

void	print_board(t_game *game, t_tetrimino mino){
	clear();
	t_field	buffer = {};
	for (int j = 0; j < mino.shape.size; j++){
		for (int i = 0; i < mino.shape.size; i++){
			if (mino.shape.array[j][i])
				buffer[mino.pos.y + j][mino.pos.x + i] = mino.shape.array[j][i];
		}
	}
	printw("%*c42 Tetris\n", WIDTH-10, ' ');
	for (int j = 0; j < HEIGHT; j++){
		for (int i = 0; i < WIDTH; i++){
			printw("%c ", (game->field[j][i] || buffer[j][i])? '#' : '.');
		}
		printw("\n");
	}
	printw("\nScore: %d\n", game->score);
}

void	print_gameover(t_game *game){
	endwin();
	for (int j = 0; j < HEIGHT; j++){
		for (int i = 0; i < WIDTH; i++){
			printf("%c ", game->field[j][i] ? '#' : '.');
		}
		printf("\n");
	}
	printf("\nGame over!\n");
	printf("\nScore: %d\n", game->score);
}
