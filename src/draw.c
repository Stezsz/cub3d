/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strodrig <strodrig@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 11:33:36 by tborges-          #+#    #+#             */
/*   Updated: 2025/06/05 16:59:22 by strodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

void	draw_line(t_player *player, t_game *game, float start_x, int i)
{
	if (game->textures && game->textures->north)
		draw_textured_line(player, game, start_x, i);
	else
		draw_simple_line(player, game, start_x, i);
}

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
