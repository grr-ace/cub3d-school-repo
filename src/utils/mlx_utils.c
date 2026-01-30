/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:18:42 by grmullin          #+#    #+#             */
/*   Updated: 2025/06/12 11:46:42 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(t_game *game)
{
	free_game(game);
	exit(0);
}

int	key_press(int key, t_game *game)
{
	if (key == UP)
		game->player.up_dir = true;
	if (key == DOWN)
		game->player.down_dir = true;
	if (key == LEFT)
		game->player.left_dir = true;
	if (key == RIGHT)
		game->player.right_dir = true;
	if (key == TURN_LEFT)
		game->player.left_rotate = true;
	if (key == TURN_RIGHT)
		game->player.right_rotate = true;
	if (key == ESCAPE)
		close_window(game);
	return (0);
}

int	key_release(int key, t_game *game)
{
	if (key == UP)
		game->player.up_dir = false;
	if (key == DOWN)
		game->player.down_dir = false;
	if (key == LEFT)
		game->player.left_dir = false;
	if (key == RIGHT)
		game->player.right_dir = false;
	if (key == TURN_LEFT)
		game->player.left_rotate = false;
	if (key == TURN_RIGHT)
		game->player.right_rotate = false;
	return (0);
}

void	hooks_init(t_game *game)
{
	mlx_hook(game->mlx_window, 2, 1L << 0, key_press, game);
	mlx_hook(game->mlx_window, 3, 1L << 1, key_release, game);
	mlx_loop_hook(game->mlx, create_window, game);
	mlx_hook(game->mlx_window, KeyPress, KeyPressMask, key_press, game);
	mlx_hook(game->mlx_window, 17, 0, close_window, game);
}
