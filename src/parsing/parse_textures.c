/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:56:14 by grmullin          #+#    #+#             */
/*   Updated: 2025/07/03 14:49:48 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*clean_path(char *path)
{
	char	*new_path;
	int		len;
	int		i;

	len = ft_strlen(path);
	while (len > 0 && (path[len - 1] == ' ' || path[len - 1] == '\n'))
	{
		path[len - 1] = '\0';
		len--;
	}
	i = 0;
	while (is_whitespace(path[i]))
		i++;
	new_path = ft_substr(path, i, len - i);
	return (new_path);
}

static int	validate_texture_path(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

int	add_texture_path(t_game *game, char *line)
{
	char	*path;

	path = ft_strchr(line, ' ');
	path = clean_path(path);
	if (ft_strncmp(line, "NO", 2) == 0)
	{
		game->textures.north.path = ft_strdup(path);
		return (free(path), 1);
	}
	else if (ft_strncmp(line, "SO", 2) == 0)
	{
		game->textures.south.path = ft_strdup(path);
		return (free(path), 1);
	}
	else if (ft_strncmp(line, "WE", 2) == 0)
	{
		game->textures.west.path = ft_strdup(path);
		return (free(path), 1);
	}
	else if (ft_strncmp(line, "EA", 2) == 0)
	{
		game->textures.east.path = ft_strdup(path);
		return (free(path), 1);
	}
	return (0);
}

int	parse_textures(t_game *game, char *line)
{
	char	*path;
	char	*tmp;
	int		i;

	i = 2;
	while (line[i] == ' ')
		i++;
	if (!line[i])
		return (print_error("Error: Missing texture path"), 0);
	path = ft_strdup(&line[i]);
	if (!path)
		return (print_error("Error: Memory allocation failed"), 0);
	tmp = path;
	path = clean_path(path);
	free(tmp);
	if (!validate_texture_path(path) || !add_texture_path(game, line))
	{
		free(path);
		return (print_error("Error: Invalid texture"), 0);
	}
	free(path);
	return (1);
}
