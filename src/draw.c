/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 11:33:36 by tborges-          #+#    #+#             */
/*   Updated: 2025/06/01 23:27:09 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_square(t_ipoint pos, int size, int color, t_game *game)
{
	t_ipoint	dx_dy;

	dx_dy.x = 1;
	dx_dy.y = 0;
	draw_sqaure_aux(pos, dx_dy, size, color, game);
	dx_dy.x = 0;
	dx_dy.y = 1;
	draw_sqaure_aux(pos, dx_dy, size, color, game);
	pos.x += size;
	draw_sqaure_aux(pos, dx_dy, size, color, game);
	dx_dy.x = 1;
	dx_dy.y = 0;
	pos.x -= size;
	pos.y += size;
	draw_sqaure_aux(pos, dx_dy, size, color, game);
}

void	draw_map(t_game *game)
{
	char		**map;
	int			color;
	t_ipoint	pos;

	map = game->map;
	color = 0x0000FF;
	for (int y = 0; map[y]; y++)
		for (int x = 0; map[y][x]; x++)
			if (map[y][x] == '1')
			{
				pos.x = x * BLOCK;
				pos.y = y * BLOCK;
				draw_square(pos, BLOCK, color, game);
			}
}

void	draw_line(t_player *player, t_game *game, float start_x, int i)
{
	float		cos_angle;
	float		sin_angle;
	t_fpoint	ray;
	float		dist;
	float		height;
	int			start_y;
	int			end;

	cos_angle = cos(start_x);
	sin_angle = sin(start_x);
	ray = player->pos;
	while (!touch(ray, game))
	{
		if (DEBUG)
			put_pixel(ray.x, ray.y, 0xFF0000, game);
		ray.x += cos_angle;
		ray.y += sin_angle;
	}
	if (!DEBUG)
	{
		dist = fixed_dist(player->pos, ray, game);
		height = (BLOCK / dist) * (WIDTH / 2);
		start_y = (HEIGHT - height) / 2;
		end = start_y + height;
		while (start_y < end)
		{
			put_pixel(i, start_y, 255, game);
			start_y++;
		}
	}
}

int	draw_loop(t_game *game)
{
	t_player	*player;
	float		fraction;
	float		start_x;
	int			i;
	t_ipoint	player_square;

	player = &game->player;
	move_player(player);
	clear_image(game);
	if (DEBUG)
	{
		player_square.x = player->pos.x;
		player_square.y = player->pos.y;
		draw_square(player_square, 10, 0x00FF00, game);
		draw_map(game);
	}
	fraction = PI / 3 / WIDTH;
	start_x = player->angle - PI / 6;
	i = 0;
	while (i < WIDTH)
	{
		draw_line(player, game, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
