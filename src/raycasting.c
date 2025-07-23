/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:09:29 by strodrig          #+#    #+#             */
/*   Updated: 2025/07/23 22:19:17 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Gets the wall texture for a specific side.
 */
t_texture	*get_wall_texture(t_game *game, int wall_side)
{
	if (!game->textures)
		return (NULL);
	if (wall_side == 0)
		return (game->textures->north);
	else if (wall_side == 1)
		return (game->textures->south);
	else if (wall_side == 2)
		return (game->textures->east);
	else if (wall_side == 3)
		return (game->textures->west);
	return (game->textures->north);
}

/**
 * Calculates the texture coordinates for the current ray.
 */
void	calculate_texture_coordinates(t_raycasting *ray, t_game *game, int x)
{
	(void)game;
	(void)x;
	if (!ray->wall_texture)
		return ;
	ray->tex_x = (int)(ray->wall_hit_x * ray->wall_texture->width);
	if (ray->tex_x < 0)
		ray->tex_x = 0;
	if (ray->tex_x >= ray->wall_texture->width)
		ray->tex_x = ray->wall_texture->width - 1;
}

/**
 * Draws a textured wall section based on the raycasting data.
 */
int	get_texture_color(t_texture *texture, int tex_x, int tex_y)
{
	if (!texture || !texture->data)
		return (0xFFFFFF);
	if (tex_x < 0 || tex_x >= texture->width || tex_y < 0
		|| tex_y >= texture->height)
		return (0xFFFFFF);
	return (*(int *)(texture->data + tex_y * texture->size_line
		+ tex_x * texture->bpp / 8));
}
