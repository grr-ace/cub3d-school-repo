/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:06:50 by grmullin          #+#    #+#             */
/*   Updated: 2025/06/27 12:33:53 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	up_direction(t_game *game, float new_x, float new_y, float angle)
{
	int	map_x;
	int	map_y;

	new_x += cos(angle) * PLA_STEP;
	new_y += sin(angle) * PLA_STEP;
	map_x = (int)(new_x);
	map_y = (int)(new_y);
	if (game->map.map[map_y][(int)game->player.x] == '1'
		|| game->map.map[(int)game->player.y][map_x] == '1')
		return ;
	if (game->map.map[map_y][map_x] != '1'
		|| game->map.map[map_y][map_x] != '\0')
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

static void	down_direction(t_game *game, float new_x, float new_y, float angle)
{
	int	map_x;
	int	map_y;

	new_x -= cos(angle) * PLA_STEP;
	new_y -= sin(angle) * PLA_STEP;
	map_x = (int)(new_x);
	map_y = (int)(new_y);
	if (game->map.map[map_y][(int)game->player.x] == '1'
		|| game->map.map[(int)game->player.y][map_x] == '1')
		return ;
	if (game->map.map[map_y][map_x] != '1'
		|| game->map.map[map_y][map_x] != '\0')
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

static void	left_direction(t_game *game, float new_x, float new_y, float angle)
{
	int	map_x;
	int	map_y;

	new_x -= sin(angle) * PLA_STEP;
	new_y += cos(angle) * PLA_STEP;
	map_x = (int)new_x;
	map_y = (int)new_y;
	if (game->map.map[map_y][(int)game->player.x] == '1'
		|| game->map.map[(int)game->player.y][map_x] == '1')
		return ;
	if (game->map.map[map_y][map_x] != '1'
		|| game->map.map[map_y][map_x] != '\0')
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

static void	right_direction(t_game *game, float new_x, float new_y, float angle)
{
	int		map_x;
	int		map_y;

	new_x += sin(angle) * PLA_STEP;
	new_y -= cos(angle) * PLA_STEP;
	map_x = (int)new_x;
	map_y = (int)new_y;
	if (game->map.map[map_y][(int)game->player.x] == '1'
		|| game->map.map[(int)game->player.y][map_x] == '1')
		return ;
	if (game->map.map[map_y][map_x] != '1'
		|| game->map.map[map_y][map_x] != '\0')
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

void	update_player(t_game *game)
{
	if (game->player.up_dir)
		up_direction(game, game->player.x,
			game->player.y, game->player.pos_angle);
	if (game->player.down_dir)
		down_direction(game, game->player.x,
			game->player.y, game->player.pos_angle);
	if (game->player.left_dir)
		left_direction(game, game->player.x,
			game->player.y, game->player.pos_angle);
	if (game->player.right_dir)
		right_direction(game, game->player.x,
			game->player.y, game->player.pos_angle);
	if (game->player.pos_angle < 0)
		game->player.pos_angle += 2 * PI;
	else if (game->player.pos_angle > 2 * PI)
		game->player.pos_angle -= 2 * PI;
	if (game->player.left_rotate)
		game->player.pos_angle -= 0.03;
	if (game->player.right_rotate)
		game->player.pos_angle += 0.03;
}
