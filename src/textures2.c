/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:09:19 by strodrig          #+#    #+#             */
/*   Updated: 2025/07/23 22:23:12 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Draws the sky background.
 */
void	put_sky(t_game *g)
{
	int	y;
	int	x;
	int	sky_x;
	int	sky_y;
	int	color;

	if (!g->textures->sky || !g->textures->sky->data)
		return ;
	y = -1;
	while (++y < HEIGHT / 2)
	{
		x = -1;
		while (++x < WIDTH)
		{
			sky_x = ((int)(x + g->sky_offset_x) % g->textures->sky->width
					+ g->textures->sky->width) % g->textures->sky->width;
			sky_y = y * g->textures->sky->height / (HEIGHT / 1.5);
			if (sky_y >= g->textures->sky->height)
				sky_y = g->textures->sky->height - 1;
			color = *(int *)(g->textures->sky->data + sky_y
					* g->textures->sky->size_line + sky_x
					* g->textures->sky->bpp / 8);
			put_pixel(x, y, color, g);
		}
	}
}

/**
 * Draws the portal gun.
 */
void	put_portal_gun(t_game *g)
{
	t_portal_gun	pg;

	if (!g->textures->portal_gun || !g->textures->portal_gun->data)
		return ;
	pg.gun_data = g->textures->portal_gun->data;
	pg.gun_width = g->textures->portal_gun->width;
	pg.gun_height = g->textures->portal_gun->height;
	pg.x_start = WIDTH - pg.gun_width / 1.7;
	pg.y_start = HEIGHT - pg.gun_height / 1.1;
	pg.y = -1;
	while (++pg.y < pg.gun_height)
	{
		pg.x = -1;
		while (++pg.x < pg.gun_width)
		{
			if (pg.x_start + pg.x >= WIDTH || pg.y_start + pg.y >= HEIGHT)
				continue ;
			pg.color = *(int *)(pg.gun_data + pg.y
					* g->textures->portal_gun->size_line
					+ pg.x * g->textures->portal_gun->bpp / 8);
			if (!(pg.color >> 24 & 0xFF))
				put_pixel(pg.x_start + pg.x, pg.y_start + pg.y, pg.color, g);
		}
	}
}

/**
 * Creates the floor and ceiling for a given column.
 */
void	create_floor_ceiling(t_game *g, int x, int wall_start, int wall_end)
{
	int	y;

	y = 0;
	while (y < wall_start)
	{
		put_pixel(x, y, g->parsed->ceiling_color, g);
		y++;
	}
	y = wall_end;
	while (y < HEIGHT)
	{
		put_pixel(x, y, g->parsed->floor_color, g);
		y++;
	}
}
