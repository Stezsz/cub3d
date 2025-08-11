/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:19:33 by tborges-          #+#    #+#             */
/*   Updated: 2025/08/11 23:26:19 by tborges-         ###   ########.fr       */
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
 * Finds the last non-empty line in the map.
 */
static int	find_last_non_empty_line(char **map, int height)
{
	int	last_non_empty_line;

	last_non_empty_line = height - 1;
	while (last_non_empty_line >= 0 && (map[last_non_empty_line][0] == '\0'
		|| map[last_non_empty_line][0] == '\n'))
		last_non_empty_line--;
	return (last_non_empty_line);
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
	last_non_empty_line = find_last_non_empty_line(map, height);
	if (!is_wall_line(map[0]) || !is_wall_line(map[last_non_empty_line]))
		return (false);
	if (!validate_middle_lines(map, last_non_empty_line + 1))
		return (false);
	if (!validate_enclosed_areas(map))
		return (false);
	return (true);
}
