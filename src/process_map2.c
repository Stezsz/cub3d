/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:19:33 by tborges-          #+#    #+#             */
/*   Updated: 2025/07/26 16:20:21 by tborges-         ###   ########.fr       */
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
 * Checks if a line is surrounded by walls.
 * This function checks if the first and last characters of the line are '1',
 * and if the line is not empty or only contains whitespace.
 */
static bool	check_line_borders(char *line)
{
	int	j;

	j = 0;
	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	if (line[j] != '1')
		return (false);
	j = 0;
	while (line[j] && line[j] != '\n')
		j++;
	j--;
	while (j >= 0 && (line[j] == ' ' || line[j] == '\t'))
		j--;
	if (j >= 0 && line[j] != '1')
		return (false);
	return (true);
}

/**
 * Validates the middle lines of the map to ensure they are surrounded by walls.
 * It checks if each line in the middle of the map starts and ends with '1'.
 * The first and last lines are already checked separately.
 */
static bool	validate_middle_lines(char **map, int height)
{
	int	i;

	i = 1;
	while (i < height - 1)
	{
		if (!check_line_borders(map[i]))
			return (false);
		i++;
	}
	return (true);
}

/**
 * Checks if a cell is valid and not a wall.
 */
static bool	is_accessible_cell(char **map, int y, int x, int height)
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
static bool	touches_boundary(char **map, int y, int x, int height)
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
static bool	flood_fill_boundary_check(char **map, int y, int x, int height,
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
 * Creates a visited matrix for flood fill algorithm.
 */
static bool	**create_visited_matrix(char **map, int height)
{
	bool	**visited;
	int		i;
	int		j;

	visited = malloc(sizeof(bool *) * height);
	if (!visited)
		return (NULL);
	i = 0;
	while (i < height)
	{
		visited[i] = malloc(sizeof(bool) * (ft_strlen(map[i]) + 1));
		if (!visited[i])
		{
			while (--i >= 0)
				free(visited[i]);
			free(visited);
			return (NULL);
		}
		j = 0;
		while (j <= (int)ft_strlen(map[i]))
		{
			visited[i][j] = false;
			j++;
		}
		i++;
	}
	return (visited);
}

/**
 * Frees the visited matrix.
 */
static void	free_visited_matrix(bool **visited, int height)
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
static bool	validate_enclosed_areas(char **map)
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

/**
 * Validates the walls of the map.
 * It checks if the first and last lines are walls, and if all middle lines
 * are also surrounded by walls.
 * Returns true if the map is valid, false otherwise.
 */
bool	validate_map_walls(char **map)
{
	int	height;
	int	last_non_empty_line;

	if (DEBUG)
		debug_print_map(map);
	height = get_map_height(map);
	last_non_empty_line = height - 1;
	while (last_non_empty_line >= 0 && (map[last_non_empty_line][0] == '\0'
		|| map[last_non_empty_line][0] == '\n'))
		last_non_empty_line--;
	if (!is_wall_line(map[0]) || !is_wall_line(map[last_non_empty_line]))
		return (false);
	if (!validate_middle_lines(map, last_non_empty_line + 1))
		return (false);
	if (!validate_enclosed_areas(map))
		return (false);
	return (true);
}
