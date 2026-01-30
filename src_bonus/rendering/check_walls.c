/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:25:56 by grmullin          #+#    #+#             */
/*   Updated: 2025/07/01 18:21:22 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_walkable_cell(char cell)
{
	if (is_texture_first_letter(cell) || cell == '0' || cell == ' ')
		return (1);
	return (0);
}

int	check_wall(t_game *game, float x, float y, float angle)
{
	int	map_x;
	int	map_y;
	int	x_check;
	int	y_check;

	x_check = (x - cos(angle)) / game->minimap.miniblock_size;
	y_check = (y - sin(angle)) / game->minimap.miniblock_size;
	map_x = (int)(x / game->minimap.miniblock_size);
	map_y = (int)(y / game->minimap.miniblock_size);
	if (map_x < 0 || map_x >= (int)game->map_width
		|| map_y < 0 || map_y >= game->map_height)
		return (1);
	if (x_check < 0 || x_check >= (int)game->map_width
		|| y_check < 0 || y_check >= game->map_height)
		return (1);
	if (!is_walkable_cell(game->map.map[map_y][x_check]))
		return (1);
	if (!is_walkable_cell(game->map.map[y_check][map_x]))
		return (1);
	if (!is_walkable_cell(game->map.map[map_y][map_x]))
		return (1);
	return (0);
}
