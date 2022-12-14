#include <stdlib.h>
#include <stdbool.h>
#include "tetrimino.h"
#include "game.h"

static const t_mino_shape	k_shapes[N_SHAPE]= {
	{
		.array = {
			{0,1,1,0},
			{1,1,0,0},
			{0,0,0,0},
			{0,0,0,0},
		},
		.size = 3,
	},
	{
		.array = {
			{1,1,0,0},
			{0,1,1,0},
			{0,0,0,0},
			{0,0,0,0},
		},
		.size = 3,
	},
	{
		.array = {
			{0,1,0,0},
			{1,1,1,0},
			{0,0,0,0},
			{0,0,0,0},
		},
		.size = 3,
	},
	{
		.array = {
			{0,0,1,0},
			{1,1,1,0},
			{0,0,0,0},
			{0,0,0,0},
		},
		.size = 3,
	},
	{
		.array = {
			{1,0,0,0},
			{1,1,1,0},
			{0,0,0,0},
			{0,0,0,0},
		},
		.size = 3,
	},
	{
		.array = {
			{1,1,0,0},
			{1,1,0,0},
			{0,0,0,0},
			{0,0,0,0},
		},
		.size = 2,
	},
	{
		.array = {
			{0,0,0,0},
			{1,1,1,1},
			{0,0,0,0},
			{0,0,0,0},
		},
		.size = 4,
	},
};

t_tetrimino tetrimino_random(){
	t_tetrimino new_mino;

	new_mino.shape = (k_shapes[rand() % N_SHAPE]);
	new_mino.pos.x = rand() % (WIDTH - new_mino.shape.size + 1);
	new_mino.pos.y = 0;
	return new_mino;
}

static bool	is_in_field(int x, int y){
	return 0 <= x && x < WIDTH && 0 <= y && y < HEIGHT;
}

bool tetrimino_is_valid_place(t_game *game, t_tetrimino mino){
	for (int j = 0; j < mino.shape.size; j++) {
		for (int i = 0; i < mino.shape.size; i++){
			int	x = mino.pos.x + i;
			int	y = mino.pos.y + j;

			if (mino.shape.array[j][i]
				&& (!is_in_field(x, y) || game->field[y][x]))
			{
				return false;
			}
		}
	}
	return true;
}

static t_point	point_add(const t_point p1, const t_point p2){
	return (t_point){p1.x + p2.x, p1.y + p2.y};
}

bool	try_move(t_game *game, t_tetrimino mino, t_point dir){
	mino.pos = point_add(mino.pos, dir);
	if (!tetrimino_is_valid_place(game, mino))
		return false;
	game->current = mino;
	return true;
}

static t_mino_shape	shape_rotate(t_mino_shape shape){
	t_mino_shape	result = shape;
	for (int j = 0; j < shape.size; j++){
		for (int i = 0; i < shape.size; i++){
			result.array[j][i] = shape.array[shape.size - 1 - i][j];
		}
	}
	return result;
}

bool	try_rotate(t_game *game, t_tetrimino mino){
	mino.shape = shape_rotate(mino.shape);
	if (!tetrimino_is_valid_place(game, mino))
		return false;
	game->current = mino;
	return true;
}
