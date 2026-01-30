/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:02:08 by grmullin          #+#    #+#             */
/*   Updated: 2025/07/03 15:06:08 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_texture(t_game *game)
{
	if (game->textures.north.path)
		free(game->textures.north.path);
	if (game->textures.south.path)
		free(game->textures.south.path);
	if (game->textures.west.path)
		free(game->textures.west.path);
	if (game->textures.east.path)
		free(game->textures.east.path);
	if (game->textures.north.image_ptr)
		mlx_destroy_image(game->mlx, game->textures.north.image_ptr);
	if (game->textures.south.image_ptr)
		mlx_destroy_image(game->mlx, game->textures.south.image_ptr);
	if (game->textures.west.image_ptr)
		mlx_destroy_image(game->mlx, game->textures.west.image_ptr);
	if (game->textures.east.image_ptr)
		mlx_destroy_image(game->mlx, game->textures.east.image_ptr);
}

int	free_game(t_game *game)
{
	if (!game)
		return (0);
	if (game->map.map)
		free_array(game->map.map);
	if (game->textures.north.path)
		free_texture(game);
	if (game->image)
	{
		if (game->image->image_ptr && game->mlx)
			mlx_destroy_image(game->mlx, game->image->image_ptr);
		free(game->image);
	}
	if (game->mlx_window && game->mlx)
		mlx_destroy_window(game->mlx, game->mlx_window);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	return (1);
}

void	free_array(char **array)
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	malloc_error(void)
{
	ft_putstr_fd("Error with malloc\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

int	mlx_error_check(t_game *game)
{
	if (game->mlx == NULL)
	{
		free(game->mlx);
		malloc_error();
	}
	else if (game->mlx_window == NULL)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		malloc_error();
	}
	else if (game->image->image_ptr == NULL)
	{
		mlx_destroy_window(game->mlx, game->mlx_window);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		malloc_error();
	}
	return (0);
}
