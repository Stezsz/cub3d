/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:09:48 by strodrig          #+#    #+#             */
/*   Updated: 2025/07/23 22:22:08 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Draws a fallback wall when no texture is available.
 * This function fills the wall section with a default color.
 */
static void	draw_fallback_wall(t_wall_data *data)
{
	int	y;

	y = data->wall_start;
	while (y < data->wall_end)
	{
		put_pixel(data->x, y, 0x808080, data->game);
		y++;
	}
}

/**
 * Initializes the texture parameters for the wall.
 */
static void	init_texture_params(t_wall_data *data, int wall_height)
{
	data->ray->tex_step = (float)data->ray->wall_texture->height / wall_height;
	data->ray->tex_pos = (data->wall_start - HEIGHT / 2 + wall_height / 2)
		* data->ray->tex_step;
	if (data->ray->tex_pos < 0)
		data->ray->tex_pos = 0;
}

/**
 * Draws a textured pixel on the wall.
 */
static void	draw_textured_pixel(t_wall_data *data, int y)
{
	int	color;

	data->ray->tex_y = (int)data->ray->tex_pos;
	if (data->ray->tex_y >= data->ray->wall_texture->height)
		data->ray->tex_y = data->ray->wall_texture->height - 1;
	if (data->ray->tex_y < 0)
		data->ray->tex_y = 0;
	data->ray->tex_pos += data->ray->tex_step;
	color = get_texture_color(data->ray->wall_texture,
			data->ray->tex_x, data->ray->tex_y);
	put_pixel(data->x, y, color, data->game);
}

/**
 * Draws a textured wall section based on the raycasting data.
 */
void	draw_textured_wall(t_wall_data *data)
{
	int		y;
	int		wall_height;

	if (!data->ray->wall_texture || !data->ray->wall_texture->data)
	{
		draw_fallback_wall(data);
		return ;
	}
	wall_height = data->ray->wall_height;
	if (wall_height <= 0)
		return ;
	init_texture_params(data, wall_height);
	y = data->wall_start;
	while (y < data->wall_end)
	{
		draw_textured_pixel(data, y);
		y++;
	}
}
