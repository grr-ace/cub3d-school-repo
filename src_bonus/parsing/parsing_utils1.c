/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 19:49:41 by grmullin          #+#    #+#             */
/*   Updated: 2025/07/05 16:56:32 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_border_e(char *line, char *next_line)
{
	int	len_1;
	int	len_2;

	len_1 = ft_strlen(line);
	len_2 = ft_strlen(next_line);
	while (is_whitespace(line[len_1]))
		len_1--;
	while (is_whitespace(next_line[len_2]))
		len_2--;
	if (next_line[len_2] == '1' || next_line[len_2 + 1] == '1')
	{
		if (len_2 == len_1 - 1 || len_2 == len_1 || len_2 == len_1 + 1)
			return (0);
	}
	return (1);
}

int	east_border_check(t_game *game)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	while (i < game->map_height)
	{
		j = 1;
		len = ft_strlen(game->map.map[i]) - 1;
		while (j < len)
		{
			if (game->map.map[i][j] == '0' && game->map.map[i][j + 1] == '1')
			{
				if (j + 2 == len)
				{
					if (is_border_e(game->map.map[i], game->map.map[i + 1]))
						return (0);
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	is_border_char_w(char *line, char *next_line)
{
	int	i;

	i = 0;
	while (is_whitespace(line[i]))
		i++;
	if (line[i] == '1' && line[i + 1] == '0')
	{
		if (next_line[i] != '1' && 
			next_line[i + 1] != '1')
			return (1);
	}
	return (0);
}

int	west_border_check(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < (int)game->map_width)
		{
			if (game->map.map[i][j] == '1' && game->map.map[i][j + 1] == '0')
			{
				if (is_border_char_w(game->map.map[i], game->map.map[i + 1]))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	borders_padded_width(t_game *game)
{
	int		i;
	int		j;

	j = 0;
	while (j < (int)game->map_width)
	{
		i = 0;
		while (i < game->map_height && is_whitespace(game->map.map[i][j]))
			i++;
		if (i < game->map_height && game->map.map[i][j] != '1')
			return (0);
		i = game->map_height - 1;
		while (i >= 0 && is_whitespace(game->map.map[i][j]))
			i--;
		if (i >= 0 && game->map.map[i][j] != '1')
			return (0);
		j++;
	}
	if (!west_border_check(game) || !east_border_check(game))
		return (0);
	return (1);
}
