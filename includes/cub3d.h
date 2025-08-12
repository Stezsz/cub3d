/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 22:11:07 by tborges-          #+#    #+#             */
/*   Updated: 2025/08/12 12:42:14 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 1280
# define HEIGHT 720
# define BLOCK 64
# define DEBUG 0

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define ESC 65307

# define PI 3.14159265359

# include "./mlx/mlx.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_ipoint
{
	int				x;
	int				y;
}					t_ipoint;

typedef struct s_fpoint
{
	float			x;
	float			y;
}					t_fpoint;

typedef struct s_move_params
{
	float			cos_angle;
	float			sin_angle;
	int				speed;
}					t_move_params;

typedef struct s_texture
{
	void			*img;
	char			*data;
	int				width;
	int				height;
	int				bpp;
	int				size_line;
	int				endian;
}					t_texture;

typedef struct s_textures
{
	t_texture		*north;
	t_texture		*south;
	t_texture		*east;
	t_texture		*west;
	t_texture		*sky;
	t_texture		*portal_gun;
}					t_textures;

// typedef struct s_map
// {
// 	int				current_fd;
// 	int				inv_north;
// 	int				inv_south;
// 	int				inv_west;
// 	int				inv_east;
// 	int				inv_floor;
// 	int				inv_ceiling;
// 	char			*north_texture;
// 	char			*south_texture;
// 	char			*west_texture;
// 	char			*east_texture;
// 	int				floor_color;
// 	int				ceiling_color;
// 	char			*line_of_map;
// 	char			**map;
// }					t_map;

typedef struct s_player
{
	t_fpoint		pos;
	float			angle;

	bool			key_up;
	bool			key_down;
	bool			key_left;
	bool			key_right;

	bool			left_rotate;
	bool			right_rotate;
}					t_player;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	void			*img;

	char			*data;
	int				bpp;
	int				size_line;
	int				endian;
	t_player		player;

	char			**map;
	t_map			*parsed;
	t_textures		*textures;
	float			sky_offset_x;
}					t_game;

typedef struct s_draw
{
	t_ipoint		x_y;
	t_ipoint		dx_dy;
	int				len;
	int				color;
	t_game			*game;
}					t_draw;

typedef struct s_portal_gun
{
	char			*gun_data;
	int				gun_width;
	int				gun_height;
	int				x_start;
	int				y_start;
	int				x;
	int				y;
	int				color;
}					t_portal_gun;

typedef struct s_raycasting
{
	t_fpoint		ray;
	float			dist;
	int				wall_side;
	t_texture		*wall_texture;
	float			wall_hit_x;
	int				tex_x;
	int				tex_y;
	float			tex_step;
	float			tex_pos;
	float			wall_height;
	int				wall_start;
	int				wall_end;
}					t_raycasting;

typedef struct s_wall_data
{
	t_game			*game;
	int				x;
	int				wall_start;
	int				wall_end;
	t_raycasting	*ray;
}					t_wall_data;

// player.c
int					key_release(int keycode, t_player *player);
int					key_press(int keycode, t_game *game);
void				move_player(t_player *player, t_game *game);
void				move_player_angle(t_player *player, float angle_speed);

// player2.c
bool				init_player_from_map(t_game *game);

// player_aux.c
void				move_player_coordinates(t_player *player,
						t_move_params params, t_game *game);

// draw.c
void				put_pixel(int x, int y, int color, t_game *game);
void				clear_image(t_game *game);
void				draw_square(t_ipoint pos, int size, int color,
						t_game *game);
void				draw_map(t_game *game);
void				cast_ray(t_fpoint *ray, t_player *player, float angle,
						t_game *game);
void				draw_textured_line(t_player *player, t_game *game,
						float start_x, int i);
void				draw_simple_line(t_player *player, t_game *game,
						float start_x, int i);
void				draw_line(t_player *player, t_game *game, float start_x,
						int i);
void				draw_debug_elements(t_game *game, t_player *player);
void				draw_rays(t_game *game, t_player *player);
int					draw_loop(t_game *game);

// draw_aux.c
void				draw_square_aux(t_draw draw);
int					determine_wall_side(t_fpoint ray_start, t_fpoint wall_hit);
float				calculate_wall_hit_x(t_fpoint wall_hit, int wall_side);
void				process_ray_casting(t_raycasting *ray_data,
						t_player *player, t_fpoint ray, t_game *game);
void				draw_textured_wall_section(t_game *game,
						t_raycasting *ray_data, int i);

// dist.c
float				distance(float delta_x, float delta_y);
float				fixed_dist(t_fpoint p1, t_fpoint p2, t_game *game);
bool				touch(t_fpoint pos, t_game *game);

// free.c
void				free_map(char **map);
int					close_game(void *param);

// parse.c
int					insert_value(t_map_errors *errors, char *line, char *check,
						int i);

// parse2.c
int					find_type(t_map_errors *errors, char *trim_line,
						char *check);
void				inset_file(int *add_direc, char **dest, char *origin);
int					find_color(char *origin, int i, int *grand_total);
void				inset_color(int *add_color, int *dest, char *origin);

// process_map3.c
void				debug_print_map(char **map);

// map_check.c
int					check_closed_map(char **map, int rows, int cols);

// textures.c
void				init_textures(t_game *g);
void				load_wall_textures(t_game *g, t_map_errors *parsed);
void				load_textures(t_game *g, t_map_errors *parsed);
void				destroy_textures(t_game *g);

// textures2.c
void				put_sky(t_game *g);
void				put_portal_gun(t_game *g);
void				create_floor_ceiling(t_game *g, int x, int wall_start,
						int wall_end);

// raycasting.c
t_texture			*get_wall_texture(t_game *game, int wall_side);
void				calculate_texture_coordinates(t_raycasting *ray,
						t_game *game, int x);
int					get_texture_color(t_texture *texture, int tex_x, int tex_y);

// raycasting2.c
void				draw_textured_wall(t_wall_data *data);

#endif
