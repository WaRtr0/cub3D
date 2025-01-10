#include "view.h"

void	layer_split(t_layer *layer, t_pixel color1, t_pixel color2)
{
	unsigned int x;
	unsigned int y;

	y = 0;
	while (y < layer->height >> 1)
	{
		x = 0;
		while (x < layer->width)
			layer_set_pixel(layer, x++, y, color1);
		y++;
	}
	while (y < layer->height)
	{
		x = 0;
		while (x < layer->width)
			layer_set_pixel(layer, x++, y, color2);
		y++;
	}
}
#include <math.h>
#include <stdio.h>
t_pixel	texture_pixel(t_layer *xpm, double x_ratio, double y_ratio)
{
	t_pixel	pixel;

	pixel = layer_get_pixel(xpm, floor(x_ratio * (double)xpm->width), y_ratio * xpm->height);
	pixel.a = 255;
	return (pixel);
}

// void draw_floor(t_game *game)
// {
//     t_game_data *data = game->data;
//     t_layer *group = layer_stack_get(game->layers, 1);
//     t_layer *render = layer_group_get(group, 2);
//     unsigned int height = HEIGHT;
    
//     // Position du joueur
//     double player_x = data->player.x + 0.5;
//     double player_y = data->player.y + 0.5;
    
//     // Calcul des vecteurs de direction
//     double yawRad = (double)data->yaw * (M_PI / 180.0);
//     double dirX = cos(yawRad);
//     double dirY = sin(yawRad);
    
//     // Plan de caméra
//     double planeX = -dirY * tan(((double)FOV / 2.0) * (M_PI / 180.0));
//     double planeY = dirX * tan(((double)FOV / 2.0) * (M_PI / 180.0));

//     // Commencer après la moitié de l'écran (sol uniquement)
//     for(int y = data->center; y < height; y++)
//     {
//         // Rayons pour les bords
//         double rayDirX0 = dirX - planeX;
//         double rayDirY0 = dirY - planeY;
//         double rayDirX1 = dirX + planeX;
//         double rayDirY1 = dirY + planeY;

//         // Position relative au centre ajustée avec le pitch
//         int p = y - data->center;

//         // Distance en fonction de la position verticale
//         double rowDistance = (0.5 * height) / p;

//         // Calcul des pas
//         double floorStepX = rowDistance * (rayDirX1 - rayDirX0) / WIDTH;
//         double floorStepY = rowDistance * (rayDirY1 - rayDirY0) / WIDTH;

//         // Position initiale
//         double floorX = player_x + rowDistance * rayDirX0;
//         double floorY = player_y + rowDistance * rayDirY0;

//         for(int x = 0; x < WIDTH; x++)
//         {
//             int cellX = (int)(floorX);
//             int cellY = (int)(floorY);

//             // Vérification des limites de la carte
//             if (cellX >= 0 && cellX < data->map->width && 
//                 cellY >= 0 && cellY < data->map->height)
//             {
//                 // Coordonnées de texture normalisées
//                 double tx = floorX - cellX;
//                 double ty = floorY - cellY;

//                 // Utilisation de votre système de texture
//                 layer_set_pixel(render, x, y,
//                     texture_pixel(layer_stack_get(game->textures, FLOOR_TEXTURE),
//                     tx, ty));
//             }

//             floorX += floorStepX;
//             floorY += floorStepY;
//         }
//     }
// }
int draw_view(t_game *game, t_game_data *raycast)
{
    t_layer *group;
    t_layer *render;
    t_layer *background;
    unsigned int scale_3d = game->scale_3d;
    double player_x = game->data->player.x + 0.5;
    double player_y = game->data->player.y + 0.5;
    int x;
    int y;
    int perceived_height;

    double yawRad = (double)game->data->yaw * (M_PI / 180.0);
    double dirX = cos(yawRad);
    double dirY = sin(yawRad);
    double planeX = -dirY * tan(((double)FOV / 2.0) * (M_PI / 180.0));
    double planeY = dirX * tan(((double)FOV / 2.0) * (M_PI / 180.0));

    // Calcul des rayons pour les colonnes
    double rayDirX0 = dirX - planeX;
    double rayDirY0 = dirY - planeY;
    double rayDirX1 = dirX + planeX;
    double rayDirY1 = dirY + planeY;

    group = layer_stack_get(game->layers, 1);
    raycast = game->data;
    render = layer_group_get(group, 2);
    background = layer_group_get(group, 1);
    raycast->center = ((HEIGHT >> 1) + (raycast->pitch * HEIGHT_PERC));
    layer_set_offset(background, 0, SPLIT_HEIGHT + raycast->pitch * HEIGHT_PERC);
    
    float posZ = 0.5 * HEIGHT;
    y = 0;
    while (y < HEIGHT)
    {
        int p = y - raycast->center;
     		double rowDistance = posZ / abs(p);
            double floorStepX = rowDistance * (rayDirX1 - rayDirX0) / WIDTH;
            double floorStepY = rowDistance * (rayDirY1 - rayDirY0) / WIDTH;
            double floorX = player_x + rowDistance * rayDirX0;
            double floorY = player_y + rowDistance * rayDirY0;

            x = 0;
            while (x < WIDTH)
            {
                perceived_height = (int)(scale_3d / raycast->ray[x].distance) >> 1;
                int wall_start = raycast->center - perceived_height;
                int wall_end = raycast->center + perceived_height;

                if (wall_start < 0) wall_start = 0;
                if (wall_end > HEIGHT) wall_end = HEIGHT;

                if (y >= wall_start && y < wall_end)
                {
                    layer_set_pixel(render, x, y,
                        texture_pixel(layer_stack_get(game->textures, raycast->ray[x].face),
                        raycast->ray[x].percent / 100.,
                        (y - (raycast->center - perceived_height)) / (perceived_height << 1)));
                }
                else if (CEIL_BONUS)
                {
                    int cellX = (int)floorX;
                    int cellY = (int)floorY;

                    if (cellX >= 0 && cellX < raycast->map->width && 
                        cellY >= 0 && cellY < raycast->map->height)
                    {
                        double tx = floorX - floor(floorX);
                        double ty = floorY - floor(floorY);

                        if (y > raycast->center)
                        {
                            // Sol
                            layer_set_pixel(render, x, y,
                                texture_pixel(layer_stack_get(game->textures, CEILING_TEXTURE),
                                tx, ty));
                        }
                        else
                        {
                            // Plafond
                            layer_set_pixel(render, x, y,
                                texture_pixel(layer_stack_get(game->textures, FLOOR_TEXTURE),
                                tx, ty));
                        }
                    }
                }
                floorX += floorStepX;
                floorY += floorStepY;
                x++;
            }
        
        y++;
    }
    return (0);
}
