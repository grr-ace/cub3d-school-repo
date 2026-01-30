/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:54:37 by grmullin          #+#    #+#             */
/*   Updated: 2025/07/05 15:32:03 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <math.h>
# include <string.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "structs.h"
# include "../Libft/libft.h"
# include "../../minilibx-linux/mlx.h"

# define BUFFER_SIZE 42
# define HEIGHT 720
# define WIDTH 1280
# define ESCAPE 65307
# define UP 119
# define DOWN 115
# define RIGHT 97
# define LEFT 100
# define TURN_LEFT 65361
# define TURN_RIGHT 65363
# define PI 3.141592653589793
# define N 4.71238898038469
# define S 1.57079632679490
# define E 6.28318530717959
# define W 3.14159265358979
# define FOV 1.04719755119660
# define NUM_RAYS WIDTH
# define PLA_STEP 0.03
# define RAY_STEP 0.01

/*				Parsing				*/
int			parse_file(t_game *game);
int			parse_textures(t_game *game, char *line);
int			parse_colors(char *line, t_colors *colors);
int			parse_map(char **lines, t_game *game);
char		**count_lines(char *file_path);
char		**fill_lines(int count, char *file_path);
int			is_valid_rgb(int r, int g, int b);
int			is_texture_first_letter(int c);
int			find_player_position(t_game *game, char **map, t_player *player);
int			free_game(t_game *game);
float		get_angle_from_char(char c);
int			is_whitespace(char c);
int			get_map_height(char **lines);
int			get_map_width(char **lines, int height, int start);
int			check_file_path(char *path);
int			check_wall(t_game *game, float x, float y, float angle);
int			borders_padded_height(t_game *game);
int			borders_padded_width(t_game *game);

/*				Utils				*/
void		print_error(char *message);
void		free_array(char **array);
char		*get_next_line(int fd);
void		malloc_error(void);
int			is_map_char(int c);
char		*clean_path(char *path);

/*			mlx/rendering			*/
int			mlx_error_check(t_game *game);
int			close_window(t_game *game);
int			key_press(int keysym, t_game *game);
void		hooks_init(t_game *game);
int			add_texture_path(t_game *game, char *line);
int			load_all_textures(t_game *game);
void		render_background(t_game *game);
int			create_window(t_game *game);
void		ft_put_pixel(t_image *image, int x, int y, int colour);
void		update_player(t_game *game);
void		minimap(t_game *game);
int			rgb_to_int(int *rgb);
void		draw_square(int x, int y, int color, t_game *game);
void		draw_rays(t_game *game, int j, int i, float angle);
void		draw_line(t_game *game, float ray_angle, int x);
void		get_textured_pixel(t_game *game, t_column_params *col, float dist);
void		get_wall_orient(t_game *game, int map_x, int map_y, float angle);
int			get_texel_color(t_image *texture, int tex_x, int tex_y);
void		put_pixel(int x, int y, int color, t_game *game);

#endif 