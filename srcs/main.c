#include "cub.h"
#include "draw.h"
#include "game.h"
#include "hook.h"
#include "layer.h"
#include "types.h"
#include "view.h"
#include "raycast.h"
#include "parsing.h"
#include "player.h"

void center_offset_player_on_map(t_game *game)
{
    t_layer *map = layer_stack_get(game->layers, 100);
    t_layer *map_mask = layer_stack_get(game->layers, 101);
    
	layer_set_offset(map,
		map_mask->width/2 - (game->data->player.x * SCALE_2D) - SCALE_2D/2 + map_mask->offset_x,
		map_mask->height/2 - (game->data->player.y * SCALE_2D) - SCALE_2D/2 + map_mask->offset_y
    );
}

t_dvector2 dvector2_rotate(t_dvector2 v, int deg)
{
	t_dvector2 new_v = {0, 0};
	double rad = deg * M_PI / 180;
	new_v.x = v.x * cos(rad) - v.y * sin(rad);
	new_v.y = v.x * sin(rad) + v.y * cos(rad);
	return (new_v);
}

t_dvector2 dvector2_add(t_dvector2 v1, t_dvector2 v2)
{
    return (t_dvector2){v1.x + v2.x, v1.y + v2.y};
}

t_dvector2 dvector2_sub(t_dvector2 v1, t_dvector2 v2)
{
    return (t_dvector2){v1.x - v2.x, v1.y - v2.y};
}

void debug_print_raycast(t_game_data *raycast)
{
	for (int i = 0; i < raycast->width; i++)
	{
		printf("Ray %d: distance: %f, percent: %f, face: %d\n", i, raycast->ray[i].distance, raycast->ray[i].percent, raycast->ray[i].face);
	}
}
void raycast(t_game *game)
{
   
    
    
    
    
    t_map *map = game->data->map;
    t_game_data *raycast;

    raycast = game->data;
    raycast->width = WIDTH;
    // raycast->ray = malloc(sizeof(t_ray*) * raycast->width);
    
    // double ray_angle = (game->data->yaw - 90 - FOV/2.0)
    // + ((double)i * FOV / raycast->width);
    t_vector2 ray_pos;
    double sub_angle = FOV / (double)raycast->width;
    double angle = game->data->yaw - 90 - (FOV >> 1);
    ray_pos.x = game->data->player.x + 0.5;
    ray_pos.y = game->data->player.y + 0.5;
    for (int i = 0; i < raycast->width; i++)
    {
        
        t_vector2 ray_dir;
        t_vector2 delta_dist;
        t_vector2 step;
        t_vector2 side_dist;
        bool hit = false;
        int side;
        
        // double ray_angle = angle + (double)i * sub_angle;
        // double ray_angle = (i - (raycast->width / 2)) * ((1. / raycast->width) * (game->data->yaw - 90));
        double ray_angle = angle + ((double)i * sub_angle);
        double angle_rad = ray_angle * (M_PI / 180.0);
        
        
        
        ray_dir.x = cos(angle_rad);
        ray_dir.y = sin(angle_rad);
        
        delta_dist.x = (ray_dir.x == 0) ? 1e30 : fabs(1.0 / ray_dir.x);
        delta_dist.y = (ray_dir.y == 0) ? 1e30 : fabs(1.0 / ray_dir.y);
        
        if (ray_dir.x < 0)
        {
            step.x = -1;
            side_dist.x = (ray_pos.x - (int)ray_pos.x) * delta_dist.x;
        }
        else
        {
            step.x = 1;
            side_dist.x = ((int)ray_pos.x + 1.0 - ray_pos.x) * delta_dist.x;
        }
        if (ray_dir.y < 0)
        {
            step.y = -1;
            side_dist.y = (ray_pos.y - (int)ray_pos.y) * delta_dist.y;
        }
        else
        {
            step.y = 1;
            side_dist.y = ((int)ray_pos.y + 1.0 - ray_pos.y) * delta_dist.y;
        }
        
        t_vector2 map_check = {(int)ray_pos.x, (int)ray_pos.y};
        // raycast->ray[i] = malloc(sizeof(t_ray));
        
        while (!hit)
        {
            if (side_dist.x < side_dist.y)
            {
                side_dist.x += delta_dist.x;
                map_check.x += step.x;
                side = 0;
            }
            else
            {
                side_dist.y += delta_dist.y;
                map_check.y += step.y;
                side = 1;
            }
            
            if (map_check.x >= 0 && map_check.x < map->width && 
                map_check.y >= 0 && map_check.y < map->height)
            {
                if (map->tiles[(int)map_check.y * map->width + (int)map_check.x] == W)
                {
                    hit = true;
                    double wall_dist;
                    double wall_x;

                    if (side == 0)
                    {
                        wall_dist = (side_dist.x - delta_dist.x);
                        wall_x = ray_pos.y + wall_dist * ray_dir.y;
                        wall_x -= floor(wall_x);
                        
                        if (ray_dir.x > 0)
                        {
                            raycast->ray[i].face = W_FACE;
                            raycast->ray[i].percent = wall_x * 100;
                        }
                        else
                        {
                            raycast->ray[i].face = E_FACE;
                            raycast->ray[i].percent = (1 - wall_x) * 100;
                        }
                    }
                    else
                    {
                        wall_dist = (side_dist.y - delta_dist.y);
                        wall_x = ray_pos.x + wall_dist * ray_dir.x;
                        wall_x -= floor(wall_x);
                        
                        if (ray_dir.y > 0)
                        {
                            raycast->ray[i].face = N_FACE;
                            raycast->ray[i].percent = wall_x * 100;
                        }
                        else
                        {
                            raycast->ray[i].face = S_FACE;
                            raycast->ray[i].percent = (1 - wall_x) * 100;
                        }
                    }
                    
                    // fish eye correction
                    raycast->ray[i].distance = wall_dist * cos((ray_angle - raycast->yaw + 90) * M_PI / 180.0);
                    
                     t_layer *map_layer = layer_stack_get(game->layers, 100);
                   
                    t_vector2 start = {
                        game->data->player.x * SCALE_2D + SCALE_2D/2,
                        game->data->player.y * SCALE_2D + SCALE_2D/2
                    };
                    t_vector2 end = {
                        (map_check.x + (side == 0 ? (step.x < 0 ? 1 : 0) : wall_x)) * SCALE_2D,
                        (map_check.y + (side == 1 ? (step.y < 0 ? 1 : 0) : wall_x)) * SCALE_2D
                    };
                    draw_line(map_layer, start, end, pixel_create(255, 0, 0, 255));
                }
            }
            else
                break;
        }
        if (!hit)
        {
            raycast->ray[i].distance = -1;
            raycast->ray[i].percent = 0;
            raycast->ray[i].face = 0;
        }
    }
    // debug_print_raycast(raycast);
}


void yaw(t_game *game)
{
    int deg = 0;
    t_dvector2 center = {SCALE_2D / 2, SCALE_2D / 2};
    t_dvector2 pos1 = {5, SCALE_2D / 2};             // Point gauche
    t_dvector2 pos2 = {SCALE_2D / 2, 5};             // Point haut
    t_dvector2 pos3 = {SCALE_2D - 5, SCALE_2D / 2};  // Point droit

    t_layer *rotate = layer_stack_get(game->layers, 104);
    layer_fill(rotate, pixel_create(0, 0, 0, 0));
    deg = game->data->yaw;

    // Soustraire le centre avant rotation
    pos1 = dvector2_sub(pos1, center);
    pos2 = dvector2_sub(pos2, center);
    pos3 = dvector2_sub(pos3, center);

    // Appliquer la rotation
    pos1 = dvector2_rotate(pos1, deg);
    pos2 = dvector2_rotate(pos2, deg);
    pos3 = dvector2_rotate(pos3, deg);

    // Réajouter le centre
    pos1 = dvector2_add(pos1, center);
    pos2 = dvector2_add(pos2, center);
    pos3 = dvector2_add(pos3, center);

    draw_triangle_fill(rotate, 
        (t_vector2){pos1.x, pos1.y}, 
        (t_vector2){pos2.x, pos2.y}, 
        (t_vector2){pos3.x, pos3.y}, 
        pixel_create(255, 255, 255, 255));
}

static void hook_mouse_move(int x, int y, t_game *game)
{
     if (game->data->is_warping)
    {
        game->data->is_warping = false;
        return;
    }
    

    int center_x = game->width / 2;
    int center_y = game->height / 2;
    
    int delta_x = x - center_x;
    int delta_y = y - center_y;
    
    if (delta_x == 0 && delta_y == 0)
        return;

    game->data->yaw += delta_x * SENTIVITY;
    game->data->pitch -= delta_y * SENTIVITY;
    
    if (game->data->pitch > PITCH_MAX)
        game->data->pitch = PITCH_MAX;
    if (game->data->pitch < -PITCH_MAX)
        game->data->pitch = -PITCH_MAX;
    
    if (game->data->yaw > YAW_MAX)
        game->data->yaw -= YAW_MAX;
    if (game->data->yaw < YAW_MIN)
        game->data->yaw += YAW_MAX;
    
    yaw(game);
    
    game->data->is_warping = true;
    mlx_mouse_move(game->mlx, game->win, center_x, center_y);
}

static void	hook(int keycode, t_game *game)
{
	t_layer	*player;
	t_layer *rotate;

	(void)game;
	(void)keycode;
	

	player = layer_stack_get(game->layers, 102);
	rotate = layer_stack_get(game->layers, 104);

	// hook script
	// example move sprite

	if (keycode == KEY_RIGHT)
	{
		game->data->player.x += 1;
		center_offset_player_on_map(game);
	}
	if (keycode == KEY_LEFT)
	{
		game->data->player.x -= 1;
		center_offset_player_on_map(game);
	}
	if (keycode == KEY_UP)
	{
		game->data->player.y -= 1;
		center_offset_player_on_map(game);
	}
	if (keycode == KEY_DOWN)
	{
		game->data->player.y += 1;
		center_offset_player_on_map(game);
	}

    if (keycode == KEY_W)
    {
        player_move(game, 1);
    }

    if (keycode == KEY_S)
    {
        player_move(game, -1);
    }
	if (keycode == KEY_A)
	{
		// layer_rotate(player, 90);
		game->data->yaw-=5;
		yaw(game);
		
	}
	if (keycode == KEY_D)
	{
		// layer_rotate(player, 90);
		game->data->yaw+=5;
		yaw(game);
		
	}

	if (keycode == KEY_SPACE)
    {
		// raycast(game);
        
    }
	// stop game
	if (keycode == KEY_ESC)
		game_handle_close(game);
}
static void	update(t_game *game)
{
	// (void)game;
	// update script
    raycast(game);
    draw_view(game);
    if (DEBUG)
    {
        game->count++;
        if (game->count >= 60)
        {
            game_handle_close(game);
        }
    }
}


static void generate_map(t_map *map_struct, t_game *game)
{
	t_layer *map;
	t_layer *map_mask;
	t_layer *circle_map;
	t_layer *player;
	t_layer *rotate;
    t_layer *raycast_debug;
	t_pixel	color;
	t_dvector2 pos = {0, 0};

	game->data->map = map_struct;
	map = layer_create(game->mlx, map_struct->width * SCALE_2D, map_struct->height * SCALE_2D, 100);
	player = layer_create(game->mlx, SCALE_2D, SCALE_2D, 102);
	map->mask = true;
	map_mask = layer_create(game->mlx, 250, 250, 101);
	circle_map = layer_create(game->mlx, 251, 251, 103);
	rotate = layer_create(game->mlx, SCALE_2D, SCALE_2D, 104);
    raycast_debug = layer_create(game->mlx,  map_struct->width * SCALE_2D, map_struct->height * SCALE_2D, 105);

	layer_stack_add(game->layers, circle_map);
	layer_stack_add(game->layers, map);
	layer_stack_add(game->layers, map_mask);
	layer_stack_add(game->layers, player);
	layer_stack_add(game->layers, rotate);
    layer_stack_add(game->layers, raycast_debug);

	layer_fill(map, pixel_create(125, 125, 125, 200));
	// draw_rect_fill(player, (t_vector2){0, 0}, (t_vector2){250, 250}, pixel_create(255, 255, 255, 255));
	draw_circle_fill(map_mask, (t_vector2){125, 125}, 125, pixel_create(0, 0, 0, 255));
	draw_circle(circle_map, (t_vector2){125, 125}, 125, pixel_create(255, 0, 0, 255));
	layer_set_offset(circle_map, 25, 25);
	draw_circle_fill(player, (t_vector2){SCALE_2D / 2, SCALE_2D / 2}, SCALE_2D / 2, pixel_create(255, 0, 0, 255));
	draw_triangle_fill(rotate, (t_vector2){0 + 5, SCALE_2D / 2}, (t_vector2){SCALE_2D / 2, 5}, (t_vector2){SCALE_2D - 5, SCALE_2D / 2}, pixel_create(255, 255, 255, 255));
	layer_set_offset(map_mask, 25, 25);
    layer_set_offset(raycast_debug, 25, 25);
	color = pixel_create(0, 0, 0, 255);
	for (pos.y = 0; pos.y < map_struct->height; pos.y++)
	{
		for (pos.x = 0; pos.x < map_struct->width; pos.x++)
		{
			if (map_struct->tiles[pos.y * map_struct->width + pos.x] == W)
				draw_rect_fill(map, (t_vector2){pos.x * SCALE_2D, pos.y * SCALE_2D},
					(t_vector2){(pos.x + 1) * SCALE_2D, (pos.y + 1) * SCALE_2D}, color);
			else if (map_struct->tiles[pos.y * map_struct->width + pos.x] == P)
			{	
				game->data->player.x = pos.x;
				game->data->player.y = pos.y;
			}
			draw_rect(map, (t_vector2){pos.x * SCALE_2D, pos.y * SCALE_2D},
				(t_vector2){(pos.x + 1) * SCALE_2D, (pos.y + 1) * SCALE_2D}, pixel_create(0, 0, 0, 175));
		}
	}
	layer_set_offset(player, 
		map_mask->width/2 - SCALE_2D / 2 + map_mask->offset_x,
		map_mask->height/2 - SCALE_2D / 2 + map_mask->offset_y
	);
	layer_set_offset(rotate, 
		map_mask->width/2 - SCALE_2D / 2 + map_mask->offset_x,
		map_mask->height/2 - SCALE_2D / 2 + map_mask->offset_y
	);
	center_offset_player_on_map(game);
    layer_volatile_on(map);

    if (WIDTH < 275*2 || HEIGHT < 275*2)
    {
        circle_map->visible = false;
        map_mask->visible = false;
        rotate->visible = false;
        player->visible = false;
        map->visible = false;
    }
}

int	main(int argc, char **argv)
{
	t_game *game;
	t_layer *wall;
	t_pixel bg_color;
	t_pixel sprite_color;
    t_layer *background;

	game = game_new(WIDTH, HEIGHT, "My Game !");
	if (!game)
		return (1);
    if (argc == 2)
    {
        if (!parse(game, argv[1]))
            return (1);
    }
    else
    {
        prerr("Error: Invalid number of arguments\n");
        return (1);
    }
    background = layer_create(game->mlx, game->width, game->height, 0);
    layer_stack_add(game->layers, background);
	game_set_hook_press(game, hook);
    game_set_hook_mouse_move(game, hook_mouse_move);
	game_set_update_callback(game, update);
    wall = layer_create(game->mlx, game->width, game->height, 2);

    generate_map(game->data->map, game);
    
    layer_stack_add(game->layers, wall);
	// bg_color = pixel_create(255, 255, 255, 255);
	// layer_fill(background, bg_color);
    layer_volatile_on(wall);
    //warning

    //test texture
    // layer_add_texture(game->mlx, game->textures, "test.xpm", 0);
    // printf("Texture added\n");
    // get basic info

    // printf("Texture Width %d\n Height %d\n", game->textures->layers[0]->width, game->textures->layers[0]->height);

    mlx_mouse_hide(game->mlx, game->win);
	game_run(game);
	game_destroy(game);
	return (0);
}
