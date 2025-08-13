/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_verify_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 17:30:00 by tborges-          #+#    #+#             */
/*   Updated: 2025/08/13 17:29:00 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

/**
 * Checks if a character represents a walkable space (0 or player)
 */
int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

/**
 * Checks if a character represents a wall
 */
int	is_wall(char c)
{
	return (c == '1');
}

/**
 * Checks if a character represents empty space/void
 */
int	is_void(char c)
{
	return (c == ' ' || c == '\0');
}

/**
 * Checks if a character is valid in the map
 * Valid: '1' (wall), '0' (empty), 'N'/'S'/'E'/'W' (player), ' ' (void)
 */
int	is_valid_char(char c)
{
	return (c == '1' || c == '0' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ' || c == '\0');
}

/**
 * Checks if coordinates are within map bounds
 */
int	is_valid_pos(t_map *map, int x, int y)
{
	return (x >= 0 && x < map->height && y >= 0 && y < map->width);
}
