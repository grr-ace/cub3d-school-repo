/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:02:34 by grmullin          #+#    #+#             */
/*   Updated: 2025/07/01 19:00:40 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_image	load_texture(void *mlx, char *path)
{
	t_image	img;

	img.image_ptr = mlx_xpm_file_to_image(mlx, path, &img.width, &img.height);
	if (!img.image_ptr)
	{
		printf ("Error: Failed to load texture:\n");
		exit (1);
	}
	img.path = path;
	img.pixels_ptr = mlx_get_data_addr(img.image_ptr, &img.bits_per_pixel,
			&img.line_len, &img.endian);
	return (img);
}

int	load_all_textures(t_game *game)
{
	game->textures.north = load_texture(game->mlx, game->textures.north.path);
	game->textures.south = load_texture(game->mlx, game->textures.south.path);
	game->textures.west = load_texture(game->mlx, game->textures.west.path);
	game->textures.east = load_texture(game->mlx, game->textures.east.path);
	return (1);
}

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	if (!game->image || !game->image->pixels_ptr)
		return ;
	index = y * game->image->line_len + x * (game->image->bits_per_pixel / 8);
	game->image->pixels_ptr[index] = color & 0xFF;
	game->image->pixels_ptr[index + 1] = (color >> 8) & 0xFF;
	game->image->pixels_ptr[index + 2] = (color >> 16) & 0xFF;
	game->image->pixels_ptr[index + 3] = (color >> 24) & 0xFF;
}

int	get_texel_color(t_image *texture, int tex_x, int tex_y)
{
	int	offset;

	offset = tex_y * texture->line_len + tex_x * (texture->bits_per_pixel / 8);
	return (*(int *)(texture->pixels_ptr + offset));
}

void	get_wall_orient(t_game *game, int map_x, int map_y, float angle)
{
	int	step_back_x;
	int	step_back_y;

	step_back_x = (int)(game->player.ray_x - cos(angle) * RAY_STEP);
	step_back_y = (int)(game->player.ray_y - sin(angle) * RAY_STEP);
	if (step_back_x < map_x && step_back_y == map_y)
	{
		game->map.wall_orient = 'E';
		game->current_texture = game->textures.east;
	}
	else if (step_back_x > map_x && step_back_y == map_y)
	{
		game->map.wall_orient = 'W';
		game->current_texture = game->textures.west;
	}
	else if (step_back_x == map_x && step_back_y < map_y)
	{
		game->map.wall_orient = 'S';
		game->current_texture = game->textures.south;
	}
	else if (step_back_x == map_x && step_back_y > map_y)
	{
		game->map.wall_orient = 'N';
		game->current_texture = game->textures.north;
	}
}
