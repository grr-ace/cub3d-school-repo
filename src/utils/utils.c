/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:57:03 by grmullin          #+#    #+#             */
/*   Updated: 2025/07/04 18:34:00 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_whitespace(char c)
{
	if (!c)
		return (1);
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}

float	get_angle_from_char(char c)
{
	if (c == 'N')
		return (N);
	else if (c == 'S')
		return (S);
	else if (c == 'E')
		return (E);
	else if (c == 'W')
		return (W);
	return (0);
}

void	print_error(char *message)
{
	printf("%s\n", message);
}
