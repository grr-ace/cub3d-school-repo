/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:55:49 by grmullin          #+#    #+#             */
/*   Updated: 2025/07/04 17:06:09 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_rgb_values(char *line, int *rgb)
{
	int	i;
	int	j;

	i = 2;
	j = 0;
	while (j < 3)
	{
		if (line[1] != ' ' || !line[i] || !ft_isdigit(line[i]))
			return (0);
		rgb[j] = ft_atoi(&line[i]);
		if (rgb[j] < 0 || rgb[j] > 255)
			return (0);
		while (ft_isdigit(line[i]))
			i++;
		if (j < 2 && line[i] != ',')
			return (0);
		if (j < 2)
			i++;
		j++;
	}
	return (1);
}

int	parse_colors(char *line, t_colors *colors)
{
	if (!line || !colors)
		return (print_error("Error: Invalid parameters"), 0);
	if (line[0] == 'F')
	{
		if (!parse_rgb_values(line, colors->floor))
			return (print_error("Error: Invalid floor color format"), 0);
	}
	else if (line[0] == 'C')
	{
		if (!parse_rgb_values(line, colors->ceiling))
			return (print_error("Error: Invalid ceiling color format"), 0);
	}
	else
		return (print_error("Error: Invalid color identifier"), 0);
	return (1);
}

int	is_valid_rgb(int r, int g, int b)
{
	return (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255);
}

int	is_map_char(int c)
{
	return (c == '1' || c == '0' || is_whitespace(c)
		|| is_texture_first_letter(c));
}
