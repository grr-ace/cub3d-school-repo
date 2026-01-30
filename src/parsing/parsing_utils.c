/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:55:57 by grmullin          #+#    #+#             */
/*   Updated: 2025/07/05 16:14:16 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_file_path(char *path)
{
	char	*type;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (1);
	type = path;
	while (ft_strlen(type) > 4)
		type++;
	if (ft_strncmp(type, ".cub", 4) != 0)
		return (1);
	return (0);
}

int	get_map_height(char **lines)
{
	int	count;
	int	i;
	int	start;

	count = 0;
	start = 0;
	while (lines[start])
	{
		i = 0;
		while (lines[start][i] == ' ' || lines[start][i] == '\t')
			i++;
		if (is_map_char(lines[start][i]))
			count++;
		start++;
	}
	return (count);
}

int	all_chars_valid(char **lines, int height)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	while (i < height)
	{
		j = 0;
		len = ft_strlen(lines[i]);
		while (j < len)
		{
			if (!is_map_char(lines[i][j]))
				return (0);
			if (is_whitespace(lines[i][j]))
				j++;
			j++;
		}
		i++;
	}
	return (1);
}

int	get_map_width(char **lines, int height, int start)
{
	int	max_width;
	int	current_width;
	int	i;

	max_width = 0;
	while (lines[start])
	{
		current_width = 0;
		i = 0;
		while (lines[start][i])
		{
			if (is_map_char(lines[start][i]))
				current_width = i + 1;
			i++;
		}
		if (current_width > max_width)
			max_width = current_width;
		if (!is_map_char(lines[start][0]) 
			&& lines[start][0] != ' ' && lines[start][0] != '\t')
			break ;
		start++;
	}
	if (!all_chars_valid(lines, height))
		return (0);
	return (max_width);
}

char	**count_lines(char *file_path)
{
	int		fd;
	char	*line;
	int		count;
	char	**lines;

	fd = open(file_path, O_RDONLY);
	count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	lines = fill_lines(count, file_path);
	if (!lines)
		return (NULL);
	return (lines);
}
