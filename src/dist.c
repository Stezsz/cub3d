/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strodrig <strodrig@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 11:38:58 by tborges-          #+#    #+#             */
/*   Updated: 2025/07/26 14:14:20 by strodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Calculates the distance between two points in 2D space.
 */
float	distance(float delta_x, float delta_y)
{
	return (sqrt(delta_x * delta_x + delta_y * delta_y));
}

/**
 * Calculates the fixed distance between two points in the game world.
 * To avoid the fisht eye effect, we need to take the player's angle
 * into account.
 */
float	fixed_dist(t_fpoint p1, t_fpoint p2, t_game *game)
{
	float	delta_x;
	float	delta_y;
	float	angle;
	float	fix_dist;

	delta_x = p2.x - p1.x;
	delta_y = p2.y - p1.y;
	angle = atan2(delta_y, delta_x) - game->player.angle;
	fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}

/**
 * Checks if a point touches a wall in the game map.
 */
bool	touch(t_fpoint pos, t_game *game)
{
	t_ipoint	map_pos;

	map_pos.x = pos.x / BLOCK;
	map_pos.y = pos.y / BLOCK;
	if (game->map[map_pos.y][map_pos.x] == '1')
		return (true);
	return (false);
}
