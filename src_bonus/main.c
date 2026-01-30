/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:57:13 by grmullin          #+#    #+#             */
/*   Updated: 2025/07/04 14:39:26 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_mlx_null(t_game *game)
{
	game->mlx = NULL;
	game->mlx_window = NULL;
	game->image = malloc(sizeof(t_image));
	if (!game->image)
	{
		free_game(game);
		exit(1);
	}
	game->image->image_ptr = NULL;
	game->image->pixels_ptr = NULL;
	game->textures.north.path = NULL;
	game->textures.south.path = NULL;
	game->textures.west.path = NULL;
	game->textures.east.path = NULL;
	game->textures.north.image_ptr = NULL;
	game->textures.south.image_ptr = NULL;
	game->textures.west.image_ptr = NULL;
	game->textures.east.image_ptr = NULL;
}

void	init_mlx_map(t_game *game)
{
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		exit (free_game(game));
	game->mlx_window = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3d");
	if (game->mlx_window == NULL)
		exit (free_game(game));
	game->image->image_ptr = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (game->image->image_ptr == NULL)
		exit (free_game(game));
	game->image->pixels_ptr = mlx_get_data_addr(game->image->image_ptr, 
			&game->image->bits_per_pixel,
			&game->image->line_len,
			&game->image->endian);
	if (!game->image->pixels_ptr)
		exit (free_game(game));
	game->minimap.miniblock_size = 20;
	game->minimap.player_size = 2;
	game->minimap.size = 20;
	game->minimap.ray_angle_step = (PI / 3) / 60;
}

void	init_player(t_game *game, int x, int y)
{
	while (game->map.map[y])
	{
		x = 0;
		while (game->map.map[y][x])
		{
			if (is_texture_first_letter(game->map.map[y][x]))
			{
				game->player.x = x;
				game->player.y = y;
				game->player.pos_angle = 
					get_angle_from_char(game->map.map[y][x]);
				break ;
			}
			x++;
		}
		y++;
	}
	game->player.up_dir = false;
	game->player.down_dir = false;
	game->player.left_dir = false;
	game->player.right_dir = false;
	game->player.left_rotate = false;
	game->player.right_rotate = false;
}

static void	init_game_null(t_game *game, char *file_path)
{
	game->file_path = file_path;
	game->map.colors.floor[0] = 0;
	game->map.colors.floor[1] = 0;
	game->map.colors.floor[2] = 0;
	game->map.colors.ceiling[0] = 0;
	game->map.colors.ceiling[1] = 0;
	game->map.colors.ceiling[2] = 0;
	game->map.map = NULL;
	game->map_width = 0;
	game->map_height = 0;
	game->map_size = 0;
	game->floor_ceiling = 0;
	game->texture_amount = 0;
	game->counter.moves = 0;
	game->counter.exit = 0;
	game->counter.player = 0;
	init_mlx_null(game);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (print_error("Error: Invalid number of arguments"), 1);
	init_game_null(&game, argv[1]);
	if (!parse_file(&game))
	{
		free_game(&game);
		return (1);
	}
	init_mlx_map(&game);
	init_player(&game, 0, 0);
	load_all_textures(&game);
	hooks_init(&game);
	mlx_loop_hook(game.mlx, create_window, &game);
	mlx_loop(game.mlx);
	return (0);
}
