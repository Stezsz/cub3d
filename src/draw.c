/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 11:33:36 by tborges-          #+#    #+#             */
/*   Updated: 2025/06/04 01:43:09 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_square(t_ipoint pos, int size, int color, t_game *game)
{
	t_draw	draw;

	draw.x_y = pos;
	draw.len = size;
	draw.color = color;
	draw.game = game;
	draw.dx_dy.x = 1;
	draw.dx_dy.y = 0;
	draw_square_aux(draw);
	draw.dx_dy.x = 0;
	draw.dx_dy.y = 1;
	draw_square_aux(draw);
	draw.x_y.x += size;
	draw_square_aux(draw);
	draw.dx_dy.x = 1;
	draw.dx_dy.y = 0;
	draw.x_y.x -= size;
	draw.x_y.y += size;
	draw_square_aux(draw);
}

void	draw_map(t_game *game)
{
	char		**map;
	int			color;
	t_ipoint	pos;
	t_ipoint	p;

	map = game->map;
	color = 0x0000FF;
	p.y = 0;
	while (map[p.y])
	{
		p.x = 0;
		while (map[p.y][p.x])
		{
			if (map[p.y][p.x] == '1')
			{
				pos.x = p.x * BLOCK;
				pos.y = p.y * BLOCK;
				draw_square(pos, BLOCK, color, game);
			}
			p.x++;
		}
		p.y++;
	}
}

void	draw_line(t_player *player, t_game *game, float start_x, int i)
{
	t_fpoint	ray;
	float		dist;
	int			start_y;
	int			end;
	float		height;

	ray = player->pos;
	while (!touch(ray, game))
	{
		if (DEBUG)
			put_pixel(ray.x, ray.y, 0xFF0000, game);
		ray.x += cos(start_x);
		ray.y += sin(start_x);
	}
	if (!DEBUG)
	{
		dist = fixed_dist(player->pos, ray, game);
		height = (BLOCK / dist) * (WIDTH / 2);
		start_y = (HEIGHT - height) / 2;
		end = start_y + height;
		while (start_y < end)
			put_pixel(i, start_y++, 255, game);
	}
}

int	draw_loop(t_game *game)
{
	t_player	*player;
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
	start_x = player->angle - PI / 6;
	i = 0;
	while (i < WIDTH)
	{
		draw_line(player, game, start_x, i++);
		start_x += PI / 3 / WIDTH;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
