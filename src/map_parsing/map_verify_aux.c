/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_verify_aux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:54:30 by tborges-          #+#    #+#             */
/*   Updated: 2025/08/13 17:29:00 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static void	init_directions(int dx[8], int dy[8])
{
	dx[0] = -1;
	dx[1] = -1;
	dx[2] = -1;
	dx[3] = 0;
	dx[4] = 0;
	dx[5] = 1;
	dx[6] = 1;
	dx[7] = 1;
	dy[0] = -1;
	dy[1] = 0;
	dy[2] = 1;
	dy[3] = -1;
	dy[4] = 1;
	dy[5] = -1;
	dy[6] = 0;
	dy[7] = 1;
}

/**
 * Checks the 8 neighbors of a position to see if any is void (space)
 * Returns 1 if map is invalid (found void neighbor), 0 if valid
 */
int	check_neighbors_for_void(t_map_data *map, int x, int y)
{
	int	dx[8];
	int	dy[8];
	int	i;
	int	nx;
	int	ny;

	init_directions(dx, dy);
	i = 0;
	while (i < 8)
	{
		nx = x + dx[i];
		ny = y + dy[i];
		if (!is_valid_pos(map, nx, ny))
			return (1);
		if (is_void(map->map[nx][ny]))
			return (1);
		i++;
	}
	return (0);
}

/**
 * Recursive flood fill function that marks visited walkable positions
 * and checks if they're properly surrounded by walls
 * Returns 1 if map is invalid, 0 if valid
 */
int	flood_fill_check(t_map_data *map, char **visited, int x, int y)
{
	if (!is_valid_pos(map, x, y))
		return (0);
	if (visited[x][y] == '1' || is_wall(map->map[x][y]))
		return (0);
	if (!is_walkable(map->map[x][y]))
		return (0);
	visited[x][y] = '1';
	if (check_neighbors_for_void(map, x, y))
	{
		ft_printf("Invalid opening found at position (%d, %d)\n", x, y);
		return (1);
	}
	if (flood_fill_check(map, visited, x - 1, y)
		|| flood_fill_check(map, visited, x + 1, y)
		|| flood_fill_check(map, visited, x, y - 1)
		|| flood_fill_check(map, visited, x, y + 1))
		return (1);
	return (0);
}

/**
 * Finds the player position in the map
 * Returns 1 if found (sets player_x, player_y), 0 if not found
 */
int	map_find_player_position(t_map_data *map, int *player_x, int *player_y)
{
	int	x;
	int	y;

	x = 0;
	while (x < map->height)
	{
		y = 0;
		while (y < map->width)
		{
			if (map->map[x][y] == 'N' || map->map[x][y] == 'S'
				|| map->map[x][y] == 'E' || map->map[x][y] == 'W')
			{
				*player_x = x;
				*player_y = y;
				return (1);
			}
			y++;
		}
		x++;
	}
	return (0);
}
