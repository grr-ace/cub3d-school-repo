/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:34:48 by grmullin          #+#    #+#             */
/*   Updated: 2025/07/04 14:29:19 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rgb_to_int(int *rgb)
{
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

void	ft_put_pixel(t_image *image, int x, int y, int colour)
{
	char	*pixel;

	if (!image || !image->pixels_ptr)
		return ;
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	pixel = image->pixels_ptr + (y * image->line_len + x
			* (image->bits_per_pixel / 8));
	*(unsigned int *)pixel = (unsigned int)colour;
}
