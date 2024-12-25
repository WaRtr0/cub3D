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
    t_layer *group = layer_stack_get(game->layers, 2);
    t_layer *map = layer_group_get(group, 0);
    t_layer *map_mask = layer_group_get(group, 1);
    
	layer_set_offset(map,
		(map_mask->width >> 1) - (game->data->player.x * SCALE_2D) - (SCALE_2D >> 1),
		(map_mask->height >> 1) - (game->data->player.y * SCALE_2D) - (SCALE_2D >> 1)
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
   t_layer *group = layer_stack_get(game->layers, 2);
    
    
    
    
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
                    
                    //  t_layer *map_layer = layer_group_get(group, 0);
                   
                    // t_vector2 start = {
                    //     game->data->player.x * SCALE_2D + SCALE_2D/2,
                    //     game->data->player.y * SCALE_2D + SCALE_2D/2
                    // };
                    // t_vector2 end = {
                    //     (map_check.x + (side == 0 ? (step.x < 0 ? 1 : 0) : wall_x)) * SCALE_2D,
                    //     (map_check.y + (side == 1 ? (step.y < 0 ? 1 : 0) : wall_x)) * SCALE_2D
                    // };
                    // draw_line(map_layer, start, end, pixel_create(255, 0, 0, 255));
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
    t_layer *map_layer = layer_group_get(group, 0);
    draw_circle_fill(map_layer, (t_vector2){game->data->player.x * SCALE_2D + SCALE_2D/2, game->data->player.y * SCALE_2D + SCALE_2D/2}, 5, pixel_create(255, 0, 0, 255));
    // debug_print_raycast(raycast);
}


void yaw(t_game *game)
{
    const int size = (SCALE_2D * HIT_BOX);
    int deg;
    t_dvector2 center = {size, size};
    t_dvector2 pos1 = {(size >> 2), size};             // Point gauche
    t_dvector2 pos2 = {size, (size >> 2)};             // Point haut
    t_dvector2 pos3 = {(size * 2) - (size >> 2), size};  // Point droit

    t_layer *cursor = layer_stack_get(game->layers, 3);
    t_layer *rotate = layer_group_get(cursor, 2);
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

    int center_x = game->width >> 1;
    int center_y = game->height >> 1;
    
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
		game->data->yaw-=5;
		yaw(game);
		
	}
	if (keycode == KEY_D)
	{
		game->data->yaw+=5;
		yaw(game);
		
	}

	if (keycode == KEY_SPACE)
    {
		;
    }
    if (keycode == KEY_SHIFT)
    {
        game->player_state.running = 1;
    }
	// stop game
	if (keycode == KEY_ESC)
		game_handle_close(game);
}

static void	hook_release(int keycode, t_game *game)
{
    if (keycode == KEY_SHIFT)
    {
        game->player_state.running = 0;
    }
}
static void	update(t_game *game)
{
	// (void)game;
	// update script
    raycast(game);
    draw_view(game, game->data);
    if (DEBUG)
    {
        game->count++;
        if (game->count >= MAX_FRAME)
        {
            game_handle_close(game);
        }
    }
}


static void generate_map(t_map *map_struct, t_game *game)
{
    //group layer
    t_layer *group;
    t_layer *cursor;

    //layer
	t_layer *map;
	t_layer *map_mask;
	t_layer *circle_map;
	t_layer *player;
	t_layer *rotate;
    t_layer *raycast_debug;
	t_pixel	color;
	t_dvector2 pos = {0, 0};

	// game->data->map = map_struct;
    

    group = layer_group_create(MAP_SIZE,MAP_SIZE, 2);
    cursor = layer_group_create(SCALE_2D * HIT_BOX * 2,SCALE_2D * HIT_BOX * 2, 3);

    layer_stack_add(game->layers, group);
    layer_stack_add(game->layers, cursor);

	map = layer_create(game->mlx, map_struct->width * SCALE_2D, map_struct->height * SCALE_2D, 0);
    raycast_debug = layer_create(game->mlx,  map_struct->width * SCALE_2D, map_struct->height * SCALE_2D, 5);
	map_mask = layer_create(game->mlx, MAP_SIZE, MAP_SIZE, 1);
    map_mask->mask = true;
	circle_map = layer_create(game->mlx, MAP_SIZE, MAP_SIZE, 3);

	player = layer_create(game->mlx, SCALE_2D * HIT_BOX * 2, SCALE_2D * HIT_BOX * 2, 1);
	rotate = layer_create(game->mlx, SCALE_2D * HIT_BOX * 2, SCALE_2D * HIT_BOX * 2, 2);

	layer_group_add(group, circle_map);
	layer_group_add(group, map);
	layer_group_add(group, map_mask);
    layer_group_add(group, raycast_debug);

	layer_group_add(cursor, player);
	layer_group_add(cursor, rotate);

	layer_fill(map, pixel_create(125, 125, 125, 200));
	draw_circle_fill(map_mask, (t_vector2){MAP_SIZE / 2, MAP_SIZE / 2}, MAP_SIZE / 2, pixel_create(0, 0, 0, 255));

    draw_circle(circle_map, (t_vector2){MAP_SIZE / 2, MAP_SIZE / 2}, MAP_SIZE / 2 - 5, pixel_create(255, 255, 0, 255));
    draw_circle(circle_map, (t_vector2){MAP_SIZE / 2, MAP_SIZE / 2}, MAP_SIZE / 2 - 4, pixel_create(200, 200, 0, 255));
    draw_circle(circle_map, (t_vector2){MAP_SIZE / 2, MAP_SIZE / 2}, MAP_SIZE / 2 - 3, pixel_create(150, 150, 0, 255));
	draw_circle(circle_map, (t_vector2){MAP_SIZE / 2, MAP_SIZE / 2}, MAP_SIZE / 2 - 2, pixel_create(150, 150, 0, 255));
    draw_circle(circle_map, (t_vector2){MAP_SIZE / 2, MAP_SIZE / 2}, MAP_SIZE / 2 - 1, pixel_create(100, 100, 0, 255));
    draw_circle(circle_map, (t_vector2){MAP_SIZE / 2, MAP_SIZE / 2}, MAP_SIZE / 2, pixel_create(50, 50, 0, 255));

	draw_circle_fill(player, (t_vector2){SCALE_2D * HIT_BOX, SCALE_2D * HIT_BOX}, SCALE_2D * HIT_BOX, pixel_create(255, 0, 0, 255));
	yaw(game);
	layer_set_offset(group, 25, 25);
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
	layer_set_offset(cursor, 
		map_mask->width/2 - SCALE_2D * HIT_BOX + group->offset_x,
		map_mask->height/2 - SCALE_2D * HIT_BOX + group->offset_y
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
    t_layer *group;
	t_layer *wall;

	game = game_new(OUTPUT_WIDTH, OUTPUT_HEIGHT, "My Game !");
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
    
	game_set_hook_press(game, hook);
    game_set_hook_release(game, hook_release);
    game_set_hook_mouse_move(game, hook_mouse_move);
	game_set_update_callback(game, update);
    generate_map(game->data->map, game);
    
    group = layer_stack_get(game->layers, 1);
    wall = layer_create(game->mlx, WIDTH, HEIGHT, 2);
    layer_group_add(group, wall);
    layer_volatile_on(wall);

    mlx_mouse_hide(game->mlx, game->win);
	game_run(game);
	game_destroy(game);
	return (0);
}
