/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:56:08 by grmullin          #+#    #+#             */
/*   Updated: 2025/07/05 15:39:10 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	player_can_move(char **map, t_player *player)
{
	int	x;
	int	y;

	x = player->x;
	y = player->y;
	if ((map[y][x - 1] != '0') && (map[y][x + 1] != '0')
		&& (map[y - 1][x] != '0') && (map[y + 1][x] != '0'))
		return (0);
	return (1);
}

int	player_is_valid(char **map, t_player *player, int count)
{
	if (count < 1)
		return (print_error("Error: Invalid map"), 0);
	if (count > 1)
		return (print_error("Error: Multiple players found"), 0);
	if (!player_can_move(map, player))
		return (print_error("Error: Invalid map - player cannot move"), 0);
	return (1);
}

int	is_texture_first_letter(int c)
{
	return (c == 'W' || c == 'E' || c == 'N' || c == 'S');
}

int	find_player_position(t_game *game, char **map, t_player *player)
{
	int	player_count;
	int	x;
	int	y;

	player_count = 0;
	x = 0;
	while (x < game->map_height)
	{
		y = 0;
		while (y < (int)game->map_width - 1)
		{
			if (!is_whitespace(map[x][y]) && is_texture_first_letter(map[x][y]))
			{
				player->x = y;
				player->y = x;
				player->direction = map[x][y];
				player_count++;
			}
			y++;
		}
		x++;
	}
	if (player_is_valid(map, player, player_count))
		return (1);
	return (0);
}
