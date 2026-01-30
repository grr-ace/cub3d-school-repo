/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:55:57 by grmullin          #+#    #+#             */
/*   Updated: 2025/07/03 15:08:35 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	file_is_valid(t_game *game)
{
	int		fd;
	char	*line;
	size_t	len;

	fd = open(game->file_path, O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		len = ft_strlen(line);
		if (len >= 12 && (ft_strnstr(line, "textures/", len)))
			game->texture_amount++;
		else if (len >= 1 && ((ft_strncmp(line, "F", 1) == 0)
				|| (ft_strncmp(line, "C", 1) == 0)))
			game->floor_ceiling++;
		else if (ft_strnstr(line, "1", len))
			game->map_size++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (game->texture_amount != 4 || game->floor_ceiling != 2
		|| game->map_size < 3)
		return (print_error("Error: Invalid map"), 0);
	return (1);
}

char	**fill_lines(int count, char *file_path)
{
	char	**lines;
	char	*line;
	int		fd;
	int		i;

	if (count < 10)
		return (print_error("Error: Invalid map"), NULL);
	lines = malloc(sizeof(char *) * (count + 1));
	if (!lines)
		return (print_error("Error: Memory allocation failed"), NULL);
	fd = open(file_path, O_RDONLY);
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		lines[i] = line;
		i++;
		line = get_next_line(fd);
	}
	lines[i] = NULL;
	close(fd);
	return (lines);
}

int	invalid_char(char **lines)
{
	int	i;
	int	j;

	i = 0;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j] && is_whitespace(lines[i][j]))
			j++;
		if (lines[i][j] == '\0')
		{
			i++;
			continue ;
		}
		if (!is_map_char(lines[i][j])
			&& lines[i][j] != 'F' && lines[i][j] != 'C')
			return (print_error("Invalid character on the map"), 1);
		i++;
	}
	return (0);
}

int	parse_lines(t_game *game, char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		if (is_texture_first_letter(lines[i][0]))
		{
			if (!parse_textures(game, lines[i]))
				return (free_array(lines), 0);
		}
		else if (lines[i][0] == 'F' || lines[i][0] == 'C')
		{
			if (!parse_colors(lines[i], &game->map.colors))
				return (free_array(lines), 0);
		}
		else if (lines[i][0] == '1' || lines[i][0] == ' ' || lines[i][0] == '0')
		{
			if (!parse_map(lines + i, game))
				return (free_array(lines), 0);
			break ;
		}
		i++;
	}
	return (1);
}

int	parse_file(t_game *game)
{
	char	**lines;
	int		fd;

	if (!game->file_path || !game || check_file_path(game->file_path))
		return (print_error("Error: Invalid parameters"), 0);
	lines = count_lines(game->file_path);
	if (!lines)
		return (0);
	fd = open(game->file_path, O_RDONLY);
	if (fd == -1)
		return (print_error("Error: Cannot open file"), 0);
	close(fd);
	if (!file_is_valid(game))
		return (free_array(lines), 0);
	if (invalid_char(lines))
		return (free_array(lines), 0);
	if (!parse_lines(game, lines))
		return (0);
	free_array(lines);
	return (1);
}
