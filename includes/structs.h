/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:54:37 by grmullin          #+#    #+#             */
/*   Updated: 2025/07/01 19:02:05 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "cub3d.h"

typedef struct s_image
{
	void	*image_ptr; 
	char	*pixels_ptr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
	char	*path;
	int		height;
	int		width;
}	t_image;

typedef struct s_column_params
{
	int	x;
	int	start;
	int	end;
}	t_column_params;

typedef struct s_draw_params
{
	int		x;
	int		start;
	int		end;
	int		tex_x;
	double	tex_pos;
	double	step;
}	t_draw_params;

typedef struct s_textures
{
	t_image	north;
	t_image	south;
	t_image	west;
	t_image	east;
}	t_textures;

typedef struct s_colors
{
	int		floor[3];
	int		ceiling[3];
}	t_colors;

typedef struct s_player
{
	float	x;
	float	y;
	float	ray_x;
	float	ray_y;
	float	pos_angle;
	bool	up_dir;
	bool	down_dir;
	bool	left_dir;
	bool	right_dir;
	bool	left_rotate;
	bool	right_rotate;
	char	direction;
}	t_player;

typedef struct s_map_counter
{
	int	moves;
	int	player;
	int	exit;
}	t_map_counter;

typedef struct s_minimap
{
	int		miniblock_size;
	int		player_size;
	int		size;
	float	ray_start_angle;
	float	ray_angle_step;
}	t_minimap;

typedef struct s_map
{
	t_colors	colors;
	char		wall_orient;
	char		**map;
	void		*img;
}	t_map;

typedef struct s_game
{
	char			*file_path;
	void			*mlx;
	void			*mlx_window;
	t_image			*image;
	t_textures		textures;
	t_image			current_texture;
	t_player		player;
	char			*data;
	int				bpp;
	int				size_line;
	int				endian;
	size_t			map_width;
	t_map			map;
	int				map_height;
	int				texture_amount;
	int				floor_ceiling;
	int				map_size;
	t_map_counter	counter;
	t_minimap		minimap;
}	t_game;

#endif