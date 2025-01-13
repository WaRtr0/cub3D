#include "cub.h"
#include "game.h"
#include "hook.h"
#include "layer.h"
#include "utils.h"
#include "draw.h"

static inline t_triangle_points	init_triangle_points(void)
{
	static const int	size = (SCALE_2D * HIT_BOX);
	t_triangle_points	points;

	points.center = (t_dvector2){size, size};
	points.pos1 = (t_dvector2){(size >> 2), size};
	points.pos2 = (t_dvector2){size, (size >> 2)};
	points.pos3 = (t_dvector2){(size * 2) - (size >> 2), size};
	return (points);
}

static inline void	apply_rotation(t_dvector2 *pos, t_dvector2 center, int deg)
{
	*pos = dvector2_sub(*pos, center);
	*pos = dvector2_rotate(*pos, deg);
	*pos = dvector2_add(*pos, center);
}

static void	yaw(t_game *game)
{
	t_triangle_points	points;
	t_layer				*rotate;

	points = init_triangle_points();
	rotate = layer_group_get(layer_stack_get(game->layers, 3), 2);
	layer_fill(rotate, pixel_create(0, 0, 0, 0));
	apply_rotation(&points.pos1, points.center, game->data->yaw);
	apply_rotation(&points.pos2, points.center, game->data->yaw);
	apply_rotation(&points.pos3, points.center, game->data->yaw);
	draw_triangle_fill(rotate,
		(t_triangle_vector){
		(t_vector2){points.pos1.x, points.pos1.y},
		(t_vector2){points.pos2.x, points.pos2.y},
		(t_vector2){points.pos3.x, points.pos3.y}},
		pixel_create(255, 255, 255, 255));
}

void	hook_no_display_mouse_move(int x, int y, t_game *game)
{
	static const int	center_x = OUTPUT_WIDTH >> 1;
	static const int	center_y = OUTPUT_HEIGHT >> 1;
	const int			delta_x = x - center_x;
	const int			delta_y = y - center_y;

	if (game->data->is_warping)
	{
		game->data->is_warping = false;
		return ;
	}
	if (delta_x == 0 && delta_y == 0)
		return ;
	game->data->yaw += delta_x * SENTIVITY;
	game->data->pitch = fmax(-PITCH_MAX, fmin(
				game->data->pitch - delta_y * SENTIVITY, PITCH_MAX));
	game->data->yaw = fmod(
			game->data->yaw - YAW_MIN, YAW_MAX - YAW_MIN) + YAW_MIN;
	yaw(game);
	game->data->is_warping = true;
	mlx_mouse_move(game->mlx, game->win, center_x, center_y);
}
