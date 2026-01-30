/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:26:01 by grmullin          #+#    #+#             */
/*   Updated: 2025/06/12 10:24:45 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	minimap(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	game->minimap.size = game->minimap.miniblock_size;
	while (game->map.map[y])
	{
		x = 0;
		while (game->map.map[y][x])
		{
			if (game->map.map[y][x] == '1')
				draw_square(x * game->minimap.miniblock_size, 
					y * game->minimap.miniblock_size, 0xFFFFFF, game);
			else if (game->map.map[y][x] == '0' || game->map.map[y][x] == ' '
				|| is_texture_first_letter(game->map.map[y][x]))
				draw_square(x * game->minimap.miniblock_size,
					y * game->minimap.miniblock_size, 0x000000, game);
			x++;
		}
		y++;
	}
	game->minimap.size = game->minimap.player_size;
	draw_square(game->player.x * game->minimap.miniblock_size, 
		game->player.y * game->minimap.miniblock_size, 0x00FF00, game);
	draw_rays(game, 0, 0, 0);
}

void	render_background(t_game *game)
{
	int	x;
	int	y;
	int	ceiling;
	int	floor;

	ceiling = rgb_to_int(game->map.colors.ceiling);
	floor = rgb_to_int(game->map.colors.floor);
	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
			ft_put_pixel(game->image, x++, y, ceiling);
		y++;
	}
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
			ft_put_pixel(game->image, x++, y, floor);
		y++;
	}
}
