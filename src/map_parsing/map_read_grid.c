/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read_grid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:00:00 by tborges-          #+#    #+#             */
/*   Updated: 2025/08/14 14:51:47 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

/**
 * Checks if line marks the start of the map
 */
static int	is_map_start(char *line)
{
	return (line[0] == ' ' || line[0] == '1');
}

/**
 * Processes a single line during map reading
 */
static int	process_map_line(char *line, char **map_lines, int *i, int *found)
{
	if (!(*found) && !is_map_start(line))
	{
		free(line);
		return (0);
	}
	if (!(*found))
		*found = 1;
	if (line[0] == '\n' || line[0] == '\0')
	{
		free(line);
		return (-1);
	}
	map_lines[*i] = line;
	(*i)++;
	return (1);
}

/**
 * Reads map lines from file descriptor
 */
int	read_map_lines_from_fd(int fd, char **map_lines, int height)
{
	char	*line;
	int		map_found;
	int		i;
	int		result;

	map_found = 0;
	i = 0;
	line = get_next_line(fd);
	while (line != NULL && i < height)
	{
		result = process_map_line(line, map_lines, &i, &map_found);
		if (result == -1)
			break ;
		if (result == 0)
		{
			line = get_next_line(fd);
			continue ;
		}
		line = get_next_line(fd);
	}
	return (i);
}

/**
 * Allocates and sets up map lines array
 */
static char	**allocate_map_lines(char *filename, int fd, int *height)
{
	char	**map_lines;

	*height = count_map_lines_from_file(filename);
	if (*height == 0)
		return (NULL);
	map_lines = malloc(sizeof(char *) * (*height + 1));
	if (!map_lines)
		return (NULL);
	*height = read_map_lines_from_fd(fd, map_lines, *height);
	map_lines[*height] = NULL;
	return (map_lines);
}

/**
 * Reads the map grid from the file
 */
char	**read_map_grid(char *filename, int fd, int *height, int *width)
{
	char	**map_lines;

	map_lines = allocate_map_lines(filename, fd, height);
	if (!map_lines)
		return (NULL);
	*width = calculate_max_width(map_lines, *height);
	normalize_map_lines(map_lines, *height, *width);
	return (map_lines);
}
