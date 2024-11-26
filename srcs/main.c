#include "cub.h"
#include "draw.h"
#include "game.h"
#include "hook.h"
#include "layer.h"
#include "types.h"
#include "raycast.h"

static void	update(t_game *game)
{
	(void)game;
	// update script
}

void center_offset_player_on_map(t_game *game)
{
    t_layer *map = layer_stack_get(game->layers, 100); // La map
    t_layer *map_mask = layer_stack_get(game->layers, 101); // Le masque
    
	layer_set_offset(map,
		map_mask->width/2 - (game->data->player.x * SCALE_2D) - SCALE_2D/2 + map_mask->offset_x,
		map_mask->height/2 - (game->data->player.y * SCALE_2D) - SCALE_2D/2 + map_mask->offset_y
    );
}
#include <math.h>
#define M_PI 3.14159265358979323846
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

// void raycast(t_game *game)
// {
// 	t_dvector2	player;
// 	t_vector2	player_dir;
// 	t_map		*map;
// 	int		 	fov = 60;

// 	map = game->data->map;
// 	player = game->data->player;
// 	player_dir = (t_vector2){cos(game->data->player_dir * M_PI / 180), sin(game->data->player_dir * M_PI / 180)};
// 	printf("Player: %d %d | dir: %f %f\n", player.x, player.y, player_dir.x, player_dir.y);
// }


// void free_raycast(t_raycast raycast)
// {
//     if (!raycast)
//         return;
//     for (int i = 0; i < raycast->width; i++)
//     {
//         free(raycast->ray[i]);
//     }
//     // free(raycast->ray);
//     free(raycast);
// }

void debug_print_raycast(t_game_data *raycast)
{
	for (int i = 0; i < raycast->width; i++)
	{
		printf("Ray %d: distance: %f, percent: %f, face: %d\n", i, raycast->ray[i].distance, raycast->ray[i].percent, raycast->ray[i].face);
	}
}
void raycast(t_game *game)
{
    t_vector2 ray_pos;
    t_vector2 ray_dir;
    t_vector2 delta_dist;
    t_vector2 side_dist;
    t_vector2 step;
    t_map *map = game->data->map;
    int fov = 60;
    t_game_data *raycast;

    raycast = game->data;
    // Création de la structure de retour
    raycast->width = 1920;
    // raycast->ray = malloc(sizeof(t_ray*) * raycast->width);
    
    for (int i = 0; i < raycast->width; i++)
    {
        bool hit = false;
        int side;
        
        double ray_angle = (game->data->player_dir - 90 - fov/2.0) + ((double)i * fov / raycast->width);
        double angle_rad = ray_angle * M_PI / 180.0;
        
        ray_pos.x = game->data->player.x + 0.5;
        ray_pos.y = game->data->player.y + 0.5;
        
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
                    double wall_x;  // Point d'impact sur le mur

                    if (side == 0)
                    {
                        wall_dist = (side_dist.x - delta_dist.x);
                        wall_x = ray_pos.y + wall_dist * ray_dir.y;
                        wall_x -= floor(wall_x);
                        
                        // Déterminer la face E ou O
                        if (ray_dir.x > 0)
                        {
                            raycast->ray[i].face = O_FACE;  // Face Ouest
                            raycast->ray[i].percent = wall_x * 100;
                        }
                        else
                        {
                            raycast->ray[i].face = E_FACE;  // Face Est
                            raycast->ray[i].percent = (1 - wall_x) * 100;
                        }
                    }
                    else
                    {
                        wall_dist = (side_dist.y - delta_dist.y);
                        wall_x = ray_pos.x + wall_dist * ray_dir.x;
                        wall_x -= floor(wall_x);
                        
                        // Déterminer la face N ou S
                        if (ray_dir.y > 0)
                        {
                            raycast->ray[i].face = N_FACE;  // Face Nord
                            raycast->ray[i].percent = wall_x * 100;
                        }
                        else
                        {
                            raycast->ray[i].face = S_FACE;  // Face Sud
                            raycast->ray[i].percent = (1 - wall_x) * 100;
                        }
                    }
                    
                    // Calculer la distance perpendiculaire pour éviter l'effet fisheye
                    raycast->ray[i].distance = wall_dist * cos((ray_angle - raycast->player_dir + 90) * M_PI / 180.0);
                    
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
            raycast->ray[i].distance = -1;  // Aucun mur trouvé
            raycast->ray[i].percent = 0;
            raycast->ray[i].face = 0;  // Face par défaut
        }
    }
    debug_print_raycast(raycast);
}

void player_dir(t_game *game)
{
    int deg = 0;
    t_dvector2 center = {SCALE_2D / 2, SCALE_2D / 2};
    t_dvector2 pos1 = {5, SCALE_2D / 2};             // Point gauche
    t_dvector2 pos2 = {SCALE_2D / 2, 5};             // Point haut
    t_dvector2 pos3 = {SCALE_2D - 5, SCALE_2D / 2};  // Point droit

    t_layer *rotate = layer_stack_get(game->layers, 104);
    layer_fill(rotate, pixel_create(0, 0, 0, 0));
    deg = game->data->player_dir;

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
	if (keycode == KEY_A)
	{
		// layer_rotate(player, 90);
		game->data->player_dir-=15;
		player_dir(game);
		
	}
	if (keycode == KEY_D)
	{
		// layer_rotate(player, 90);
		game->data->player_dir+=15;
		player_dir(game);
		
	}

	if (keycode == KEY_SPACE)
    {
		// raycast(game);
        raycast(game);
        draw_view(game);
    }
	// stop game
	if (keycode == KEY_ESC)
		game_handle_close(game);
}

	// fake parsings
static t_map	*get_parsed_map(void)
{
	t_map	*map;
	t_map_tile	*tiles;

	map = (t_map *)malloc(sizeof(t_map));
	map->width = 10;
	map->height = 10;
	tiles = (t_map_tile *)malloc(sizeof(t_map_tile) * map->width * map->height);
	
	map->tiles = tiles;

	static const t_map_tile map_tile[10][10] = {
		{W, W, W, W, W, W, W, W, W, W},
		{W, E, E, W, W, E, E, E, E, W},
		{W, E, E, E, W, E, E, E, E, W},
		{W, E, E, E, W, W, W, E, E, W},
		{W, E, E, E, E, W, E, E, E, W},
		{W, E, E, P, E, E, E, E, E, W},
		{W, E, E, E, E, E, W, E, E, W},
		{W, E, E, E, E, E, W, D, W, W},
		{W, E, E, E, E, E, W, E, E, W},
		{W, W, W, W, W, W, W, W, W, W},
	};
	
	 for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
        tiles[y * map->width + x] = map_tile[y][x]; // Indexation 1D
        }
    }
	return (map);
}


static void generate_map(t_map *map_struct, t_game *game)
{
	t_layer *map;
	t_layer *map_mask;
	t_layer *circle_map;
	t_layer *player;
	t_layer *rotate;
	t_pixel	color;
	t_dvector2 pos = {0, 0};

	game->data->map = map_struct;
	map = layer_create(game->mlx, map_struct->width * SCALE_2D, map_struct->height * SCALE_2D, 100);
	player = layer_create(game->mlx, SCALE_2D, SCALE_2D, 102);
	map->mask = true;
	map_mask = layer_create(game->mlx, 250, 250, 101);
	circle_map = layer_create(game->mlx, 251, 251, 103);
	rotate = layer_create(game->mlx, SCALE_2D, SCALE_2D, 104);

	layer_stack_add(game->layers, circle_map);
	layer_stack_add(game->layers, map);
	layer_stack_add(game->layers, map_mask);
	layer_stack_add(game->layers, player);
	layer_stack_add(game->layers, rotate);
	layer_fill(map, pixel_create(125, 125, 125, 200));
	// draw_rect_fill(player, (t_vector2){0, 0}, (t_vector2){250, 250}, pixel_create(255, 255, 255, 255));
	draw_circle_fill(map_mask, (t_vector2){125, 125}, 125, pixel_create(0, 0, 0, 255));
	draw_circle(circle_map, (t_vector2){125, 125}, 125, pixel_create(255, 0, 0, 255));
	layer_set_offset(circle_map, 25, 25);
	draw_circle_fill(player, (t_vector2){SCALE_2D / 2, SCALE_2D / 2}, SCALE_2D / 2, pixel_create(255, 0, 0, 255));
	draw_triangle_fill(rotate, (t_vector2){0 + 5, SCALE_2D / 2}, (t_vector2){SCALE_2D / 2, 5}, (t_vector2){SCALE_2D - 5, SCALE_2D / 2}, pixel_create(255, 255, 255, 255));
	layer_set_offset(map_mask, 25, 25);
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
}

int	main(void)
{
	t_game *game;
	t_layer *background;
	t_layer *sprite;
	t_layer *sprite_mask;
	t_pixel bg_color;
	t_pixel sprite_color;

	game = game_new(1920, 1080, "My Game !");
	if (!game)
		return (1);
	game_set_hook(game, hook);
	game_set_update_callback(game, update);
	background = layer_create(game->mlx, game->width, game->height, 0);

	layer_stack_add(game->layers, background);
	bg_color = pixel_create(255, 255, 255, 255);
	layer_fill(background, bg_color);
	generate_map(get_parsed_map(), game);
	game_run(game);
	game_destroy(game);
	return (0);
}
