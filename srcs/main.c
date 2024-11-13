
#include "game.h"
#include "layer.h"
#include "draw.h"
#include "hook.h"

static void	update(t_game *game)
{
	(void)game;
	// update script
}

static void	hook(int keycode, t_game *game)
{
	(void)game;
	(void)keycode;
	// hook script
	//example move sprite

	t_layer	*sprite;
	sprite = layer_stack_get(game->layers, 1);
	if (keycode == KEY_RIGHT)
	{
		layer_set_offset(sprite, sprite->offset_x + 10, sprite->offset_y);
	}
	if (keycode == KEY_LEFT)
	{
		layer_set_offset(sprite, sprite->offset_x - 10, sprite->offset_y);
	}
	if (keycode == KEY_UP)
	{
		layer_set_offset(sprite, sprite->offset_x, sprite->offset_y - 10);
	}
	if (keycode == KEY_DOWN)
	{
		layer_set_offset(sprite, sprite->offset_x, sprite->offset_y + 10);
	}

	// stop game
	if (keycode == KEY_ESC)
		game_handle_close(game);
}

int	main(void)
{
	t_game	*game;
	t_layer	*background;
	t_layer	*sprite;
	t_pixel	bg_color;
	t_pixel	sprite_color;

	game = game_new(1920, 1080, "My Game !");
	if (!game)
		return (1);
	game_set_hook(game, hook);
	game_set_update_callback(game, update);
	background = layer_create(game->mlx, game->width, game->height, 0);
	sprite = layer_create(game->mlx, 500, 500, 1);
	draw_xpm_texture(game->mlx, sprite, (t_vector2){0, 0}, "assets/textures/test.xpm");

	layer_stack_add(game->layers, background);
	layer_stack_add(game->layers, sprite);
	layer_set_offset(sprite, game->width / 2 - 500, game->height / 2 - 500);
	bg_color = pixel_create(255, 255, 255, 255);
	layer_fill(background, bg_color);
	sprite_color = pixel_create(255, 0, 0, 255);
	draw_triangle_fill(background, (t_vector2){game->width / 4, game->height
		/ 4}, (t_vector2){game->width / 4 * 3, game->height / 4},
		(t_vector2){game->width / 4 * 2, game->width / 4 * 2}, pixel_create(0,
			255, 255, 255));
	game_run(game);
	game_destroy(game);
	return (0);
}
