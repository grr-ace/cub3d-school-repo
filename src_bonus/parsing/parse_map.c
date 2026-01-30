/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:56:08 by grmullin          #+#    #+#             */
/*   Updated: 2025/07/05 15:31:12 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_single_one(t_game *game)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		count = 0;
		while (j < (int)game->map_width)
		{
			if (game->map.map[i][j] == '1')
				count++;
			j++;
		}
		if (count == 1)
			return (1);
		i++;
	}
	return (0);
}

int	borders_padded_height(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < (int)game->map_width && is_whitespace(game->map.map[i][j]))
			j++;
		if (j < (int)game->map_width && game->map.map[i][j] != '1')
			return (0);
		j = (int)game->map_width - 1;
		while (j > 0 && is_whitespace(game->map.map[i][j]))
			j--;
		if (j >= 0 && game->map.map[i][j] != '1')
			return (0);
		if (i > 0 && is_whitespace(game->map.map[i][j]))
			return (0);
		if (check_single_one(game))
			return (0);
		i++;
	}
	return (1);
}

int	fill_map(t_game *game, char **lines, int i, size_t j)
{
	while (i < game->map_height)
	{
		game->map.map[i] = malloc(sizeof(char) * (game->map_width + 1));
		if (!game->map.map[i])
		{
			while (i > 0)
				free(game->map.map[--i]);
			free(game->map.map);
			game->map.map = NULL;
			return (print_error("Error: Memory allocation failed"), 0);
		}
		j = 0;
		while (j < game->map_width)
		{
			if (j < ft_strlen(lines[i]) && is_map_char(lines[i][j]))
				game->map.map[i][j] = lines[i][j];
			else
				game->map.map[i][j] = '\t';
			j++;
		}
		game->map.map[i][j] = '\0';
		i++;
	}
	game->map.map[i] = NULL;
	return (1);
}

int	parse_map(char **lines, t_game *game)
{
	int	i;

	i = 0;
	game->map_height = get_map_height(lines);
	if (game->map_height == 0)
		return (print_error("Error: Invalid map"), 0);
	game->map_width = get_map_width(lines, game->map_height, 0);
	if (game->map_width == 0)
		return (print_error("Error: Invalid map"), 0);
	game->map.map = malloc(sizeof(char *) * (game->map_height + 1));
	if (!game->map.map)
		return (print_error("Error: Memory allocation failed"), 0);
	while (i <= game->map_height)
		game->map.map[i++] = NULL;
	if (!fill_map(game, lines, 0, 0))
		return (print_error("Error: Memory allocation failed"), 0);
	if (!borders_padded_height(game) || !borders_padded_width(game))
		return (print_error("Error: Invalid map"), 0);
	if (!find_player_position(game, game->map.map, &game->player))
	{
		free_array(game->map.map);
		game->map.map = NULL;
		return (0);
	}
	return (1);
}
