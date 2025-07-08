/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:19:33 by tborges-          #+#    #+#             */
/*   Updated: 2025/07/09 00:22:10 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdbool.h>
#include <string.h>

static int	get_map_height(char **map)
{
	int	height;

	height = 0;
	while (map[height])
		height++;
	return (height);
}

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
	return (true);
}
