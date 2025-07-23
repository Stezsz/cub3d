/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 11:40:41 by tborges-          #+#    #+#             */
/*   Updated: 2025/07/23 22:18:53 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * [index] -> blue
 * [index + 1] -> green
 * [index + 2] -> red
 */
void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

/**
 * Clears the image by setting all pixels to black.
 */
void	clear_image(t_game *game)
{
	t_ipoint	p;

	p.y = 0;
	while (p.y < HEIGHT)
	{
		p.x = 0;
		while (p.x < WIDTH)
		{
			put_pixel(p.x, p.y, 0, game);
			p.x++;
		}
		p.y++;
	}
}

/**
 * Auxiliary function that draws a square on the screen.
 */
void	draw_square_aux(t_draw draw)
{
	int	i;

	i = 0;
	while (i < draw.len)
	{
		put_pixel(draw.x_y.x + draw.dx_dy.x * i, draw.x_y.y + draw.dx_dy.y * i,
			draw.color, draw.game);
		i++;
	}
}

/**
 * Determines which side of the wall was hit by the ray.
 * fabs is to compare the absolute values of floats.
 * 0 = north, 1 = south, 2 = east, 3 = west.
 */
int	determine_wall_side(t_fpoint ray_start, t_fpoint wall_hit)
{
	t_ipoint	map_pos;
	float		dx;
	float		dy;

	(void)ray_start;
	map_pos.x = wall_hit.x / BLOCK;
	map_pos.y = wall_hit.y / BLOCK;
	dx = wall_hit.x - (map_pos.x * BLOCK + BLOCK / 2);
	dy = wall_hit.y - (map_pos.y * BLOCK + BLOCK / 2);
	if (fabs(dx) > fabs(dy))
	{
		if (dx > 0)
			return (2);
		else
			return (3);
	}
	else
	{
		if (dy > 0)
			return (1);
		else
			return (0);
	}
}
