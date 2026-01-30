/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:41:55 by grmullin          #+#    #+#             */
/*   Updated: 2025/06/26 16:44:49 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	clear_image(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				ft_put_pixel(game->image, x, y,
					rgb_to_int(game->map.colors.ceiling));
			else
				ft_put_pixel(game->image, x, y,
					rgb_to_int(game->map.colors.floor));
			x++;
		}
		y++;
	}
}

int	create_window(t_game *game)
{
	float	start_angle;
	float	angle_step;
	float	ray_angle;
	int		i;

	clear_image(game);
	start_angle = game->player.pos_angle - (FOV / 2);
	angle_step = FOV / NUM_RAYS;
	i = 0;
	while (i < NUM_RAYS)
	{
		ray_angle = start_angle + i * angle_step;
		draw_line(game, ray_angle, i);
		i++;
	}
	update_player(game);
	mlx_put_image_to_window(game->mlx, game->mlx_window,
		game->image->image_ptr, 0, 0);
	return (0);
}
