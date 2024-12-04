#include "cub.h"
#include "draw.h"
#include "game.h"
#include "hook.h"
#include "layer.h"
#include "types.h"
#include "view.h"
#include "raycast.h"
#include "parsing.h"

void center_offset_player_on_map(t_game *game)
{
    t_layer *map = layer_stack_get(game->layers, 100);
    t_layer *map_mask = layer_stack_get(game->layers, 101);
    
	layer_set_offset(map,
		map_mask->width/2 - (game->data->player.x * SCALE_2D) - SCALE_2D/2 + map_mask->offset_x,
		map_mask->height/2 - (game->data->player.y * SCALE_2D) - SCALE_2D/2 + map_mask->offset_y
    );
}

void player_move_forward(t_game *game)
{
    t_map *map = game->data->map;
    double move_x = sin((game->data->yaw) * M_PI / 180) * SPEED;
    double move_y = -cos((game->data->yaw) * M_PI / 180) * SPEED;
    double new_x = game->data->player.x + move_x;
    double new_y = game->data->player.y + move_y;
    

    t_vector2 hit_points[4] = {
        {new_x - HIT_BOX, new_y - HIT_BOX},  // Haut gauche
        {new_x + HIT_BOX, new_y - HIT_BOX},  // Haut droite
        {new_x - HIT_BOX, new_y + HIT_BOX},  // Bas gauche
        {new_x + HIT_BOX, new_y + HIT_BOX}   // Bas droite
    };
    
    // Vérifier les limites de la carte pour tous les points
    for (int i = 0; i < 4; i++)
    {
        if (hit_points[i].x < 0 || hit_points[i].x >= map->width || 
            hit_points[i].y < 0 || hit_points[i].y >= map->height)
            return;
    }
    
    // Vérifier les collisions pour chaque point
    for (int i = 0; i < 4; i++)
    {
        int check_x = (int)floor(hit_points[i].x);
        int check_y = (int)floor(hit_points[i].y);
        
        if (map->tiles[check_y * map->width + check_x] == W)
        {
            // Si collision détectée, trouver la direction de la collision
            bool collision_x = false;
            bool collision_y = false;
            
            // Vérifier si la collision est horizontale
            if (map->tiles[(int)floor(game->data->player.y) * map->width + check_x] == W)
                collision_x = true;
                
            // Vérifier si la collision est verticale
            if (map->tiles[check_y * map->width + (int)floor(game->data->player.x)] == W)
                collision_y = true;
                
            // Appliquer le mouvement seulement dans les directions sans collision
            if (!collision_x)
                game->data->player.x = new_x;
            if (!collision_y)
                game->data->player.y = new_y;
                
            center_offset_player_on_map(game);
            return;
        }
    }
    
    // Si aucune collision n'est détectée, appliquer le mouvement complet
    game->data->player.x = new_x;
    game->data->player.y = new_y;
    center_offset_player_on_map(game);
}

void    player_move_backward(t_game *game)
{
    t_map *map = game->data->map;
    // Ajuster l'angle pour que 0 degré pointe vers le haut
    // et rotation dans le sens horaire
    double move_x = sin((game->data->yaw) * M_PI / 180) * SPEED;
    double move_y = -cos((game->data->yaw) * M_PI / 180) * SPEED;
    double new_x = game->data->player.x - move_x;
    double new_y = game->data->player.y - move_y;
    
    int current_x = (int)floor(game->data->player.x);
    int current_y = (int)floor(game->data->player.y);
    int next_x = (int)floor(new_x);
    int next_y = (int)floor(new_y);
    
    // Vérifier les limites de la carte
    if (next_x < 0 || next_x >= map->width || next_y < 0 || next_y >= map->height)
        return;
        
    // Vérifier les collisions le long du mouvement
    bool can_move_x = true;
    bool can_move_y = true;
    
    // Vérifier la collision en X
    if (map->tiles[current_y * map->width + next_x] == W)
        can_move_x = false;
        
    // Vérifier la collision en Y
    if (map->tiles[next_y * map->width + current_x] == W)
        can_move_y = false;
        
    // Vérifier la collision diagonale
    if (map->tiles[next_y * map->width + next_x] == W)
    {
        can_move_x = false;
        can_move_y = false;
    }
    
    // Appliquer le mouvement selon les collisions
    if (can_move_x)
        game->data->player.x = new_x;
    if (can_move_y)
        game->data->player.y = new_y;
        
    center_offset_player_on_map(game);
}


#include <math.h>

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
// 	t_vector2	yaw;
// 	t_map		*map;
// 	int		 	fov = 60;

// 	map = game->data->map;
// 	player = game->data->player;
// 	yaw = (t_vector2){cos(game->data->yaw * M_PI / 180), sin(game->data->yaw * M_PI / 180)};
// 	printf("Player: %d %d | dir: %f %f\n", player.x, player.y, yaw.x, yaw.y);
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
    // int fov = 60;
    t_game_data *raycast;

    raycast = game->data;
    // Création de la structure de retour
    raycast->width = WIDTH;
    // raycast->ray = malloc(sizeof(t_ray*) * raycast->width);
    
   
    for (int i = 0; i < raycast->width; i++)
    {
        bool hit = false;
        int side;
        
        double ray_angle = (game->data->yaw - 90 - FOV/2.0) + ((double)i * FOV / raycast->width);
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
                    double wall_x;

                    if (side == 0)
                    {
                        wall_dist = (side_dist.x - delta_dist.x);
                        wall_x = ray_pos.y + wall_dist * ray_dir.y;
                        wall_x -= floor(wall_x);
                        
                        if (ray_dir.x > 0)
                        {
                            raycast->ray[i].face = O_FACE;
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
        player_move_forward(game);
    }

    if (keycode == KEY_S)
    {
        player_move_backward(game);
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
    t_layer *background;
	t_layer *background_split;
	t_layer *wall;
	t_pixel bg_color;
	t_pixel sprite_color;

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
	game_set_hook_press(game, hook);
    game_set_hook_mouse_move(game, hook_mouse_move);
	game_set_update_callback(game, update);
    background = layer_create(game->mlx, game->width, game->height, 0);
	background_split = layer_create(game->mlx, game->width, game->height * 2, 1);
    wall = layer_create(game->mlx, game->width, game->height, 2);


    printf("Map:\n");
    for (int y = 0; y < game->data->map->height; y++)
    {
        for (int x = 0; x < game->data->map->width; x++)
        {
            printf("%d", game->data->map->tiles[y * game->data->map->width + x]);
        }
        printf("\n");
    }

    generate_map(game->data->map, game);
    layer_split_fill(background_split, pixel_create(25, 25, 75, 255), pixel_create(75, 25, 25, 255));
    layer_set_offset(background_split, 0, SPLIT_HEIGHT);
    layer_stack_add(game->layers, background);
	layer_stack_add(game->layers, background_split);
    layer_stack_add(game->layers, wall);
	// bg_color = pixel_create(255, 255, 255, 255);
	// layer_fill(background, bg_color);
    layer_volatile_on(wall);
    //warning
    mlx_mouse_hide(game->mlx, game->win);
	game_run(game);
	game_destroy(game);
	return (0);
}
