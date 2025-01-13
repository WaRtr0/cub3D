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

t_pixel	texture_pixel_vertical(t_layer *xpm, int x, int y)
{
	t_pixel	pixel;

	pixel = layer_get_pixel(xpm, x, y);
	pixel.a = 255;
	return (pixel);
}


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

	double rayDirX0 = dirX - planeX;
	double rayDirY0 = dirY - planeY;
	double rayDirX1 = dirX + planeX;
	double rayDirY1 = dirY + planeY;

	group = layer_stack_get(game->layers, 1);
	raycast = game->data;
	render = layer_group_get(group, 2);
	// printf("scale3d: %d\n", scale_3d);
	// printf("rayDirX0: %f\n", rayDirX0);
	// printf("rayDirY0: %f\n", rayDirY0);
	// printf("rayDirX1: %f\n", rayDirX1);
	// printf("rayDirY1: %f\n", rayDirY1);
	// printf("player_x: %f\n", player_x);
	// printf("player_y: %f\n", player_y);
	// printf("dirX: %f\n", dirX);
	// printf("dirY: %f\n", dirY);
	// printf("planeX: %f\n", planeX);
	// printf("planeY: %f\n", planeY);
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
			perceived_height = scale_3d / raycast->ray[x].distance / 2;
			// printf("perceived_height: %d\n", perceived_height);
			// perceived_height = (int)(scale_3d / raycast->ray[x].distance) >> 1;
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
				// int cellX = (int)floorX;
				// int cellY = (int)floorY;

				// if (cellX >= 0 && cellX < raycast->map->width && 
				// 	cellY >= 0 && cellY < raycast->map->height)
				// {
					// int tx = ((int)(SIZE_TEXTURE * (floorX - cellX)) & (SIZE_TEXTURE - 1));
					// int ty = ((int)(SIZE_TEXTURE * (floorY - cellY)) & (SIZE_TEXTURE - 1)) ;

		// 			  double weight = (currentDist - distPlayer) / (distWall - distPlayer);

        // double currentFloorX = weight * floorXWall + (1.0 - weight) * posX;
        // double currentFloorY = weight * floorYWall + (1.0 - weight) * posY;

        // int floorTexX, floorTexY;
        // floorTexX = int(currentFloorX * texWidth) % texWidth;
        // floorTexY = int(currentFloorY * texHeight) % texHeight;


					double merde = 0.67;
					double weight = (raycast->ray[x].distance - posZ) / (rowDistance - posZ);
					double currentFloorX = weight * floorX + (merde - weight) * player_x;
					double currentFloorY = weight * floorY + (merde - weight) * player_y;

					int floorTexX = (int)(currentFloorX * SIZE_TEXTURE) % SIZE_TEXTURE;
					int floorTexY = (int)(currentFloorY * SIZE_TEXTURE) % SIZE_TEXTURE;

					// double tx = fmod(floorX, 1.0);
					// double ty = fmod(floorY, 1.0);

					// if (tx < 0) tx += 0.5;
					// if (ty < 0) ty += 0.5;
				
					// layer_set_pixel(render, x, y,
					// 	texture_pixel_vertical(layer_stack_get(game->textures, CEILING_TEXTURE),
					// 	tx, ty));
				

					layer_set_pixel(render, x, y,
						texture_pixel(layer_stack_get(game->textures, CEILING_TEXTURE),
						floorTexX / (double)SIZE_TEXTURE,
						floorTexY / (double)SIZE_TEXTURE));
			// }
			}
			floorX += floorStepX;
			floorY += floorStepY;
			x++;
		}
		y++;
	}
	return (0);
}
