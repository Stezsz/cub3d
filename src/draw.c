/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 11:33:36 by tborges-          #+#    #+#             */
/*   Updated: 2025/07/23 21:37:09 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Draws a textured line on the screen.
 */
void	draw_textured_line(t_player *player, t_game *game, float start_x, int i)
{
	t_fpoint		ray;
	t_raycasting	ray_data;

	cast_ray(&ray, player, start_x, game);
	if (!DEBUG)
	{
		process_ray_casting(&ray_data, player, ray, game);
		draw_textured_wall_section(game, &ray_data, i);
	}
}

/**
 * Draws a simple line on the screen.
 */
void	draw_simple_line(t_player *player, t_game *game, float start_x, int i)
{
	t_fpoint	ray;
	float		dist;
	int			start_y;
	int			end;
	float		height;

	cast_ray(&ray, player, start_x, game);
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

/**
 * Draws a line on the screen.
 */
void	draw_line(t_player *player, t_game *game, float start_x, int i)
{
	if (game->textures && game->textures->north)
		draw_textured_line(player, game, start_x, i);
	else
		draw_simple_line(player, game, start_x, i);
}

/**
 * Draws debug elements on the screen.
 * This includes the player's position and the map.
 */
void	draw_debug_elements(t_game *game, t_player *player)
{
	t_ipoint	player_square;

	if (DEBUG)
	{
		player_square.x = player->pos.x;
		player_square.y = player->pos.y;
		draw_square(player_square, 10, 0x00FF00, game);
		draw_map(game);
	}
}

/**
 * Draws the rays on the screen.
 * This function iterates through the width of the screen,
 * casting rays from the player's position at different angles.
 */
void	draw_rays(t_game *game, t_player *player)
{
	float	start_x;
	int		i;

	start_x = player->angle - PI / 6;
	i = 0;
	while (i < WIDTH)
	{
		draw_line(player, game, start_x, i++);
		start_x += PI / 3 / WIDTH;
	}
}
