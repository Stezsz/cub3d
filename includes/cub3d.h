/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 22:11:07 by tborges-          #+#    #+#             */
/*   Updated: 2025/05/30 23:31:05 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 1280
# define HEIGHT 720

# define W 119
# define A 97
# define S 115
# define D 100

# define PI 3.14159265358979323846

# include "libft/libft.h"
# include "mlx/mlx.h"
# include <math.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_player
{
	double		x;
	double		y;

	bool		key_up;
	bool		key_down;
	bool		key_left;
	bool		key_right;
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
}				t_game;

void			init_player(t_player *player);
int				key_press(int keycode, t_player *player);
int				key_release(int keycode, t_player *player);
void			move_player(t_player *player);

#endif
