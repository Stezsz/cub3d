/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 22:11:07 by tborges-          #+#    #+#             */
/*   Updated: 2025/06/03 23:59:09 by tborges-         ###   ########.fr       */
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

# define PI 3.14159265359

# include "./mlx/mlx.h"
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_ipoint
{
	int			x;
	int			y;
}				t_ipoint;

typedef struct s_fpoint
{
	float		x;
	float		y;
}				t_fpoint;

typedef struct s_player
{
	t_fpoint	pos;
	float		angle;

	bool		key_up;
	bool		key_down;
	bool		key_left;
	bool		key_right;

	bool		left_rotate;
	bool		right_rotate;
}				t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;

	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
	t_player	player;

	char		**map;
}				t_game;

typedef struct s_draw
{
	t_ipoint	x_y;
	t_ipoint	dx_dy;
	int			len;
	int			color;
	t_game		*game;
}				t_draw;

// player.c
void			init_player(t_player *player);
int				key_release(int keycode, t_player *player);
int				key_press(int keycode, t_player *player);
void			move_player(t_player *player);

// player_aux.c
void			move_player_angle(t_player *player, float angle_speed);
void			move_player_coordinates(t_player *player, float cos_angle,
					float sin_angle, int speed);

// draw.c
void			put_pixel(int x, int y, int color, t_game *game);
void			clear_image(t_game *game);
void			draw_square(t_ipoint pos, int size, int color, t_game *game);
void			draw_map(t_game *game);
void			draw_line(t_player *player, t_game *game, float start_x, int i);
int				draw_loop(t_game *game);

// draw_aux.c
void			put_pixel(int x, int y, int color, t_game *game);
void			clear_image(t_game *game);
void			draw_square_aux(t_draw draw);

// dist.c
float			distance(float delta_x, float delta_y);
float			fixed_dist(t_fpoint p1, t_fpoint p2, t_game *game);
bool			touch(t_fpoint pos, t_game *game);

#endif
