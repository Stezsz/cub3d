/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:28:43 by tborges-          #+#    #+#             */
/*   Updated: 2025/08/13 18:12:55 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

/**
 * Counts the number of map lines in the file
 */
static int	count_map_lines(int fd)
{
	char	*line;
	int		count;
	int		found_map_start;

	count = 0;
	found_map_start = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (!found_map_start && (line[0] == ' ' || line[0] == '1'))
			found_map_start = 1;
		if (found_map_start)
		{
			if (line[0] == '\n' || line[0] == '\0')
				break ;
			count++;
		}
		free(line);
	}
	return (count);
}

/**
 * Calculates the maximum width of the map
 */
static int	calculate_max_width(char **map_lines, int height)
{
	int		len;
	int		max_width;
	int		i;

	max_width = 0;
	i = 0;
	while (i < height)
	{
		len = ft_strlen(map_lines[i]);
		if (len > 0 && map_lines[i][len - 1] == '\n')
			len--;
		if (len > max_width)
			max_width = len;
		i++;
	}
	return (max_width);
}

/**
 * Normalizes map lines to have the same width (pad with spaces)
 */
static void	normalize_map_lines(char **map_lines, int height, int width)
{
	int		i;
	int		j;
	char	*old_line;
	int		old_len;

	i = 0;
	while (i < height)
	{
		old_line = map_lines[i];
		old_len = ft_strlen(old_line);
		if (old_len > 0 && old_line[old_len - 1] == '\n')
		{
			old_line[old_len - 1] = '\0';
			old_len--;
		}
		map_lines[i] = malloc(width + 1);
		if (!map_lines[i])
		{
			map_lines[i] = old_line;
			return ;
		}
		j = 0;
		while (j < old_len)
		{
			map_lines[i][j] = old_line[j];
			j++;
		}
		while (j < width)
		{
			map_lines[i][j] = ' ';
			j++;
		}
		map_lines[i][width] = '\0';
		free(old_line);
		i++;
	}
}

/**
 * Reads the map grid from the file
 */
static char	**read_map_grid(int fd, int *height, int *width)
{
	char	*line;
	char	**map_lines;
	int		map_found;
	int		i;
	long	current_pos;

	map_found = 0;
	i = 0;
	current_pos = lseek(fd, 0, SEEK_CUR);
	*height = count_map_lines(fd);
	lseek(fd, current_pos, SEEK_SET);
	if (*height == 0)
		return (NULL);
	map_lines = malloc(sizeof(char *) * (*height + 1));
	if (!map_lines)
		return (NULL);
	while ((line = get_next_line(fd)) != NULL && i < *height)
	{
		if (!map_found && line[0] != ' ' && line[0] != '1')
		{
			free(line);
			continue ;
		}
		if (!map_found)
			map_found = 1;
		if (line[0] == '\n' || line[0] == '\0')
		{
			free(line);
			break ;
		}
		map_lines[i] = line;
		i++;
	}
	map_lines[i] = NULL;
	*height = i;
	if (*height == 0)
	{
		free(map_lines);
		return (NULL);
	}
	*width = calculate_max_width(map_lines, *height);
	normalize_map_lines(map_lines, *height, *width);
	return (map_lines);
}

/**
 * Initializes a map structure from a file pointer
 * Returns: pointer to initialized t_map structure, or NULL on error
 */
t_map	*map_init_from_fd(int fd)
{
	t_map *map;

	if (fd < 0)
		return (NULL);

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->map = NULL;
	map->height = 0;
	map->width = 0;
	map->map = read_map_grid(fd, &map->height, &map->width);
	if (!map->map)
	{
		free(map);
		return (NULL);
	}
	return (map);
}

/**
 * This function receives a map file path and reads the map data.
 * It is expected to parse the map and store it in a suitable data structure.
 */
t_map	*map_read(char *map_file)
{
	int fd;
	t_map *map;

	if (!map_file)
		return (NULL);
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
	{
		printf("Error: Cannot open map file %s\n", map_file);
		return (NULL);
	}
	map = map_init_from_fd(fd);
	close(fd);
	if (!map)
	{
		printf("Error: Failed to initialize map from %s\n", map_file);
		return (NULL);
	}

	return (map);
}

/**
 * Frees all memory allocated for a map structure
 */
void	map_free(t_map *map)
{
	int i;

	if (!map)
		return;

	if (map->map)
	{
		i = 0;
		while (i < map->height && map->map[i])
		{
			free(map->map[i]);
			i++;
		}
		free(map->map);
	}

	free(map);
}

/**
 * Debug function to print the map
 */
void	map_print_debug(t_map *map)
{
	int	i;

	if (!map || !map->map)
	{
		printf("Map is NULL or invalid\n");
		return ;
	}
	printf("Map dimensions: %dx%d\n", map->width, map->height);
	printf("Map content:\n");
	i = 0;
	while (i < map->height)
	{
		if (map->map[i] != NULL)
			printf("[%2d] '%s'\n", i, map->map[i]);
		else
			printf("[%2d] '(null)'\n", i);
		i++;
	}
}
