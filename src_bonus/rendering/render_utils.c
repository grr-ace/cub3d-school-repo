/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:34:48 by grmullin          #+#    #+#             */
/*   Updated: 2025/06/27 15:36:05 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rgb_to_int(int *rgb)
{
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

void	ft_put_pixel(t_image *image, int x, int y, int colour)
{
	char	*pixel;

	if (!image || !image->pixels_ptr)
		return ;
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	pixel = image->pixels_ptr + (y * image->line_len + x
			* (image->bits_per_pixel / 8));
	*(unsigned int *)pixel = (unsigned int)colour;
}

void	draw_square(int x, int y, int color, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->minimap.size)
	{
		j = 0;
		while (j < game->minimap.size)
		{
			ft_put_pixel(game->image, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_rays(t_game *game, int j, int i, float angle)
{
	float		center_x;
	float		center_y;
	float		x;
	float		y;

	center_x = game->player.x * game->minimap.miniblock_size + 
		game->minimap.player_size / 2;
	center_y = game->player.y * game->minimap.miniblock_size + 
		game->minimap.player_size / 2;
	game->minimap.ray_start_angle = game->player.pos_angle - (FOV / 2);
	while (j < 60)
	{
		angle = game->minimap.ray_start_angle + 
			j * game->minimap.ray_angle_step;
		i = 0;
		while (++i < 100)
		{
			x = center_x + cos(angle) * i;
			y = center_y + sin(angle) * i;
			if (check_wall(game, x, y, angle))
				break ;
			ft_put_pixel(game->image, (int)x, (int)y, 0xFF0000);
		}
		j++;
	}
}
