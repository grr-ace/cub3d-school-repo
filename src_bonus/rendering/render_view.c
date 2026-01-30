/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:30:00 by grmullin          #+#    #+#             */
/*   Updated: 2025/07/03 12:57:22 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static float	calc_distance(t_game *game, float ray_angle)
{
	float	ray_x;
	float	ray_y;
	size_t	map_x;
	int		map_y;

	ray_x = game->player.x;
	ray_y = game->player.y;
	while (1)
	{
		ray_x += cos(ray_angle) * RAY_STEP;
		ray_y += sin(ray_angle) * RAY_STEP;
		map_x = (int)ray_x;
		map_y = (int)ray_y;
		if ((int)map_x < 0 || map_y < 0 || map_y >= game->map_height
			|| map_x >= game->map_width)
			break ;
		if (game->map.map[map_y][map_x] == '1')
			break ;
	}
	game->player.ray_x = ray_x;
	game->player.ray_y = ray_y;
	get_wall_orient(game, (int)ray_x, (int)ray_y, ray_angle);
	return (sqrtf((ray_x - game->player.x) * (ray_x - game->player.x)
			+ (ray_y - game->player.y) * (ray_y - game->player.y)));
}

void	draw_line(t_game *game, float ray_angle, int x)
{
	float			dist;
	int				line_height;
	int				start;
	int				end;
	t_column_params	col;

	if (ray_angle < 0)
		ray_angle += 2 * PI;
	if (ray_angle > 2 * PI)
		ray_angle -= 2 * PI;
	dist = calc_distance(game, ray_angle);
	dist *= cos(ray_angle - game->player.pos_angle);
	line_height = HEIGHT / (dist + 0.5);
	if (line_height > HEIGHT)
		line_height = HEIGHT;
	start = (HEIGHT - line_height) / 2;
	if (start < 0)
		start = 0;
	end = start + line_height;
	if (end >= HEIGHT)
		end = HEIGHT;
	col.x = x;
	col.start = start;
	col.end = end;
	get_textured_pixel(game, &col, dist);
}
