/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_verify.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:13:31 by tborges-          #+#    #+#             */
/*   Updated: 2025/08/14 19:34:40 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

/**
 * Verifies if the map is properly enclosed by walls using flood fill
 * Returns 1 if map is valid (enclosed), 0 if invalid (has leaks to void)
 */
int	map_verify_enclosed(t_map_data *map)
{
	char	**visited;
	int		player_x;
	int		player_y;
	int		result;

	if (!map || !map->map)
		return (0);
	if (!map_find_player_position(map, &player_x, &player_y))
	{
		ft_putstr_fd("Error\nNo player found in map\n", 2);
		return (0);
	}
	visited = create_visited_array(map);
	if (!visited)
	{
		ft_putstr_fd("Error\nCould not allocate memory for verification\n", 2);
		return (0);
	}
	result = flood_fill_check(map, visited, player_x, player_y);
	free_visited_array(visited, map->height);
	return (!result);
}

/**
 * Counts the number of players in the map and checks if there's exactly one
 * Returns 1 if valid (exactly one player), 0 if invalid (0 or multiple players)
 */
int	map_verify_player_count(t_map_data *map)
{
	int	x;
	int	y;
	int	player_count;

	if (!map || !map->map)
		return (0);
	x = 0;
	player_count = 0;
	while (x < map->height)
	{
		y = 0;
		while (y < map->width)
		{
			if (map->map[x][y] == 'N' || map->map[x][y] == 'S'
				|| map->map[x][y] == 'E' || map->map[x][y] == 'W')
			{
				player_count++;
			}
			y++;
		}
		x++;
	}
	return (player_count == 1);
}

/**
 * Verifies if all characters in the map are valid
 * Returns 1 if all characters are valid, 0 if invalid characters found
 */
int	map_verify_characters(t_map_data *map)
{
	int	x;
	int	y;

	if (!map || !map->map)
		return (0);
	x = 0;
	while (x < map->height)
	{
		y = 0;
		while (y < map->width)
		{
			if (!is_valid_char(map->map[x][y]))
			{
				ft_printf("Error\nInvalid character '%c' (ASCII"
					"%d) found at position (%d, %d)\n",
					map->map[x][y], (int)map->map[x][y],
					x, y);
				return (0);
			}
			y++;
		}
		x++;
	}
	return (1);
}

/**
 * Comprehensive map validation that checks characters,
 * enclosure and player count. Returns 1 if map is completely valid,
 * 0 if any validation fails
 */
int	map_verify_complete(t_map_data *map)
{
	if (!map)
		return (0);
	if (!map_verify_characters(map))
	{
		ft_putstr_fd("Error\nMap contains invalid characters\n", 2);
		return (0);
	}
	if (!map_verify_player_count(map))
	{
		ft_putstr_fd("Error\nMap must contain exactly one player (N, S, E,"
			"or W)\n", 2);
		return (0);
	}
	if (!map_verify_enclosed(map))
	{
		ft_putstr_fd("Error\nMap is not properly enclosed by walls\n", 2);
		return (0);
	}
	return (1);
}
