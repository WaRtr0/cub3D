
#include "draw.h"
#include "game.h"
#include "hook.h"
#include "layer.h"
#include "font.h"

void	update(t_game *game)
{
	t_layer	*square1;
	t_layer	*square2;
	t_layer	*square3;
    // gam

	// get the squares
	square1 = layer_stack_get(game->layers, 1);
	square2 = layer_stack_get(game->layers, 4);
	square3 = layer_stack_get(game->layers, 3);
	// set random offset
	layer_set_offset(square1, 100 + (rand() % 10) - 5, 100 + (rand() % 10) - 5);
	layer_set_offset(square2, 115 + (rand() % 10) - 5, 125 + (rand() % 10) - 5);
	layer_set_offset(square3, 85 + (rand() % 10) - 5, 125 + (rand() % 10) - 5);

	game->count++;
	if (game->count == 150)
	{
		game_handle_close(game);
	}
    // printf("FPS: %d\n", (int)(1.0f / game->delta_time));
}

void	hook(int keycode, t_game *game)
{
	t_layer	*square;
    int x, y;

    square = layer_stack_get(game->layers, 2);
	if (keycode == KEY_ESC)
    {
		game_handle_close(game);
        return ;
    }
	if (keycode == KEY_A)
		printf("Key pressed: A\n");
	if (keycode == KEY_RIGHT)
	{
		printf("Key pressed: RIGHT\n");
		layer_get_offset(square, &x, &y);
		layer_set_offset(square, x + 10, y);
	}
	if (keycode == KEY_LEFT)
	{
		printf("Key pressed: LEFT\n");
		layer_get_offset(square, &x, &y);
		layer_set_offset(square, x - 10, y);
	}
	if (keycode == KEY_UP)
	{
		printf("Key pressed: UP\n");
		layer_get_offset(square, &x, &y);
		layer_set_offset(square, x, y - 10);
	}
	if (keycode == KEY_DOWN)
	{
		printf("Key pressed: DOWN\n");
		

		layer_get_offset(square, &x, &y);
		layer_set_offset(square, x, y + 10);
	}
	printf("Key pressed: %d\n", keycode);
}

void empty(t_game *game)
{
    (void)game;
}

int	main(void)
{
	t_game *game;
	t_layer *background;
	t_layer *square1_bugeffect;
	t_layer *square2_bugeffect;
	t_layer *square3_bugeffect;
	t_layer *square4_movable;

    // t_layer *fps_layer;
    t_bdf   *bdf;

    bdf = font_init_bdf();
     if (!bdf || font_parse_bdf("assets/font/ic16x16u.bdf", bdf))
    {
        printf("Failed to parse BDF file\n");
        font_free_bdf(bdf);
        return (1);
    }

	// Create a new game
	game = game_new(5*32*4, 5*32*4, "Mon Jeu");


	// Initialize the game
	if (!game || !game_init(game))
	{
		game_destroy(game);
		return (1);
	}

	// Set the hook callback
	game_set_hook(game, hook);

	// Create a new layers
	// background
	background = layer_create(game->mlx, game->width, game->height, 0);

	// create 3 squares
	square1_bugeffect = layer_create(game->mlx, 50, 50, 1);
	square2_bugeffect = layer_create(game->mlx, 50, 50, 4);
	square3_bugeffect = layer_create(game->mlx, 50, 50, 3);

	square4_movable = layer_create(game->mlx, 8, 8, 2);
    // fps_layer = layer_create(game->mlx, 64, 64, 5);

	// set offset
	layer_set_offset(square1_bugeffect, 100, 100);
	layer_set_offset(square2_bugeffect, 115, 125);
	layer_set_offset(square3_bugeffect, 85, 125);
	layer_set_offset(square4_movable, 9, 9);
    // layer_set_offset(fps_layer, 16, game->height - 64);

	// add layers to the layer stack
	// doit changer creer methode directement dans game
	layer_stack_add(game->layers, background);
	// layer_stack_add(game->layers, square1_bugeffect);
	// layer_stack_add(game->layers, square2_bugeffect);
	// layer_stack_add(game->layers, square3_bugeffect);
	layer_stack_add(game->layers, square4_movable);
    // layer_stack_add(game->layers, fps_layer);

	// create color
	t_pixel bg_color = pixel_create(255, 255, 255, 255); // white
	layer_fill(background, bg_color);
	//draw_xpm_texture(game->mlx, background, (t_vector2){0, 0}, "test.xpm");
	t_pixel sprite_color = pixel_create(255, 0, 0, 255);        // red
	layer_fill(square1_bugeffect, pixel_create(0, 255, 0, 50));
		// green transparent
	layer_fill(square2_bugeffect, pixel_create(255, 0, 0, 50));
		// red transparent
	layer_fill(square3_bugeffect, pixel_create(0, 0, 255, 50));
		// blue transparent

	// layer_fill(square4_movable, pixel_create(75, 0, 75, 255));  // purple
	draw_circle_fill(square4_movable, (t_vector2){5, 5}, 4, pixel_create(0,
			0, 0, 255));
    // draw_triangle_fill(square4_movable, (t_vector2){0, 0}, (t_vector2){64, 0},
    //         (t_vector2){32, 64}, pixel_create(0, 255, 255, 255));
    draw_triangle_fill(square4_movable, (t_vector2){16, 48}, (t_vector2){48, 48},
            (t_vector2){32, 16}, pixel_create(0, 255, 255, 255));
    layer_set_pixel(square4_movable, 32, 32, pixel_create(255, 255, 255, 255));




    // t_font font = (t_font){bdf, 50, pixel_create(255, 0, 0, 255)};
    // draw_text(background, (t_vector2){32, 32*10}, &font, "SALUT");

	// add update callback
	game_set_update_callback(game, update);
	// Run the game
	game_run(game);
    game_destroy(game);
    font_free_bdf(bdf);
	return (0);
}
