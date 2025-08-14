/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:28:43 by tborges-          #+#    #+#             */
/*   Updated: 2025/08/14 11:50:03 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

/**
 * Initializes a map structure from a file pointer
 * Returns: pointer to initialized t_map structure, or NULL on error
 */
t_map	*map_init_from_fd(char *filename, int fd)
{
	t_map	*map;

	if (fd < 0)
		return (NULL);
	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->map = NULL;
	map->height = 0;
	map->width = 0;
	map->map = read_map_grid(filename, fd, &map->height, &map->width);
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
	int		fd;
	t_map	*map;

	if (!map_file)
		return (NULL);
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
	{
		printf("Error: Cannot open map file %s\n", map_file);
		return (NULL);
	}
	map = map_init_from_fd(map_file, fd);
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
	int	i;

	if (!map)
		return ;
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
