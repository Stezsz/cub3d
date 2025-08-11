/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 00:00:00 by tborges-          #+#    #+#             */
/*   Updated: 2025/08/11 23:29:47 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Gets the height of the map.
 */
static int	get_map_height(char **map)
{
	int	height;

	height = 0;
	while (map[height])
		height++;
	return (height);
}

/**
 * Creates a visited matrix for flood fill algorithm.
 */
bool	**create_visited_matrix(char **map, int height)
{
	bool	**visited;
	int		i;

	visited = malloc(sizeof(bool *) * height);
	if (!visited)
		return (NULL);
	i = 0;
	while (i < height)
	{
		if (!init_visited_row(visited, map, i))
		{
			while (--i >= 0)
				free(visited[i]);
			free(visited);
			return (NULL);
		}
		i++;
	}
	return (visited);
}

/**
 * Frees the visited matrix.
 */
void	free_visited_matrix(bool **visited, int height)
{
	int	i;

	if (!visited)
		return ;
	i = 0;
	while (i < height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

/**
 * Validates that all accessible areas are properly enclosed by walls.
 */
bool	validate_enclosed_areas(char **map)
{
	int		height;
	int		y;
	int		x;
	bool	**visited;
	bool	is_valid;

	height = get_map_height(map);
	visited = create_visited_matrix(map, height);
	if (!visited)
		return (false);
	is_valid = true;
	y = 0;
	while (y < height && is_valid)
	{
		x = 0;
		while (x < (int)ft_strlen(map[y]) && is_valid)
		{
			if (is_accessible_cell(map, y, x, height) && !visited[y][x])
			{
				if (flood_fill_boundary_check(map, y, x, height, visited))
					is_valid = false;
			}
			x++;
		}
		y++;
	}
	free_visited_matrix(visited, height);
	return (is_valid);
}
