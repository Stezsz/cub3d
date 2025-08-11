/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 00:00:00 by tborges-          #+#    #+#             */
/*   Updated: 2025/08/11 23:29:47 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Checks if a cell is valid and not a wall.
 */
bool	is_accessible_cell(char **map, int y, int x, int height)
{
	int	width;

	if (y < 0 || y >= height)
		return (false);
	if (x < 0)
		return (false);
	width = ft_strlen(map[y]);
	if (x >= width)
		return (false);
	return (map[y][x] != '1' && map[y][x] != ' ');
}

/**
 * Checks if an accessible cell touches the map boundary.
 */
bool	touches_boundary(char **map, int y, int x, int height)
{
	int	width;

	width = ft_strlen(map[y]);
	if (y == 0 || y == height - 1)
		return (true);
	if (x == 0 || x == width - 1)
		return (true);
	if (y > 0 && x < (int)ft_strlen(map[y - 1]))
		if (map[y - 1][x] == ' ')
			return (true);
	if (y < height - 1 && x < (int)ft_strlen(map[y + 1]))
		if (map[y + 1][x] == ' ')
			return (true);
	if (x > 0 && map[y][x - 1] == ' ')
		return (true);
	if (x < width - 1 && map[y][x + 1] == ' ')
		return (true);
	return (false);
}

/**
 * Flood fill to check if accessible areas touch map boundaries.
 */
bool	flood_fill_boundary_check(char **map, int y, int x, int height,
		bool **visited)
{
	if (!is_accessible_cell(map, y, x, height) || visited[y][x])
		return (false);
	visited[y][x] = true;
	if (touches_boundary(map, y, x, height))
		return (true);
	if (flood_fill_boundary_check(map, y - 1, x, height, visited)
		|| flood_fill_boundary_check(map, y + 1, x, height, visited)
		|| flood_fill_boundary_check(map, y, x - 1, height, visited)
		|| flood_fill_boundary_check(map, y, x + 1, height, visited))
		return (true);
	return (false);
}

/**
 * Initializes a row of the visited matrix.
 */
bool	init_visited_row(bool **visited, char **map, int i)
{
	int	j;

	visited[i] = malloc(sizeof(bool) * (ft_strlen(map[i]) + 1));
	if (!visited[i])
		return (false);
	j = 0;
	while (j <= (int)ft_strlen(map[i]))
	{
		visited[i][j] = false;
		j++;
	}
	return (true);
}
