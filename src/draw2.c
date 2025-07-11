/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:59:02 by strodrig          #+#    #+#             */
/*   Updated: 2025/07/11 22:09:02 by tborges-         ###   ########.fr       */
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

void	cast_ray(t_fpoint *ray, t_player *player, float angle, t_game *game)
{
	*ray = player->pos;
	while (!touch(*ray, game))
	{
		if (DEBUG)
			put_pixel(ray->x, ray->y, 0xFF0000, game);
		ray->x += cos(angle);
		ray->y += sin(angle);
	}
}

int	draw_loop(t_game *game)
{
	t_player	*player;

	player = &game->player;
	move_player(player, game);
	clear_image(game);
	if (!DEBUG && game->textures && game->textures->sky)
		put_sky(game);
	draw_debug_elements(game, player);
	draw_rays(game, player);
	if (!DEBUG && game->textures && game->textures->portal_gun)
		put_portal_gun(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
