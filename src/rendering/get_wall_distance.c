/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall_distance.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:48:29 by grmullin          #+#    #+#             */
/*   Updated: 2025/07/03 12:58:10 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static float	get_visible_portion(float dist)
{
	float	min_portion;
	float	max_portion;
	float	zoom_dist;
	float	visible_portion;

	min_portion = 0.15f;
	max_portion = 1.0f;
	zoom_dist = 0.8f;
	if (dist > zoom_dist)
		visible_portion = max_portion;
	else
		visible_portion = min_portion + 
			(max_portion - min_portion) * (dist / zoom_dist);
	if (visible_portion < min_portion)
		visible_portion = min_portion;
	if (visible_portion > max_portion)
		visible_portion = max_portion;
	return (visible_portion);
}

static int	get_tex_x(t_game *game)
{
	float	wall_hit_x;
	float	wall_hit_y;
	int		tex_x;

	wall_hit_x = game->player.ray_x - floor(game->player.ray_x);
	wall_hit_y = game->player.ray_y - floor(game->player.ray_y);
	if (game->map.wall_orient == 'N' || game->map.wall_orient == 'S')
		tex_x = (int)(wall_hit_x * game->current_texture.width);
	else
		tex_x = (int)(wall_hit_y * game->current_texture.width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= game->current_texture.width)
		tex_x = game->current_texture.width - 1;
	return (tex_x);
}

static void	draw_texture_column(t_game *game, t_draw_params *params)
{
	int	tex_y;
	int	color;

	while (params->start < params->end)
	{
		tex_y = (int)params->tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= game->current_texture.height)
			tex_y = game->current_texture.height - 1;
		color = get_texel_color(&game->current_texture, params->tex_x, tex_y);
		put_pixel(params->x, params->start, color, game);
		params->tex_pos += params->step;
		params->start++;
	}
}

t_draw_params	init_params(t_column_params *col, t_game *game, int tex_pos, 
	double step)
{
	t_draw_params	params;
	int				tex_x;

	tex_x = get_tex_x(game);
	params.x = col->x;
	params.start = col->start;
	params.end = col->end;
	params.tex_x = tex_x;
	params.tex_pos = tex_pos;
	params.step = step;
	return (params);
}

void	get_textured_pixel(t_game *game, t_column_params *col, float dist)
{
	float			visible_portion;
	float			texture_start;
	double			step;
	double			tex_pos;
	t_draw_params	params;

	visible_portion = get_visible_portion(dist);
	texture_start = (1.0f - visible_portion) / 2.0f * 
		game->current_texture.height;
	step = visible_portion * game->current_texture.height / 
		(col->end - col->start);
	tex_pos = texture_start + 
		(col->start - HEIGHT / 2 + (col->end - col->start) / 2) * step;
	params = init_params(col, game, tex_pos, step);
	draw_texture_column(game, &params);
}
