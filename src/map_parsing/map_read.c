/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:28:43 by tborges-          #+#    #+#             */
/*   Updated: 2025/09/01 22:48:00 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

/**
 * Initializes a map structure from a file pointer
 * Returns: pointer to initialized t_map_data structure, or NULL on error
 */
t_map_data	*map_init_from_fd(char *filename, int fd)
{
	t_map_data	*map;

	if (fd < 0)
		return (NULL);
	map = malloc(sizeof(t_map_data));
	if (!map)
		return (NULL);
	map->map = NULL;
	map->height = 0;
	map->width = 0;
	map->north_texture = NULL;
	map->south_texture = NULL;
	map->east_texture = NULL;
	map->west_texture = NULL;
	map->floor_color = -1;
	map->ceiling_color = -1;
	map->map = read_map_grid(filename, fd, &map->height, &map->width);
	if (!map->map)
	{
		free(map);
		return (NULL);
	}
	return (map);
}

/*
** Opens and validates the map file
** Returns: file descriptor, or -1 on error
*/
static int	open_map_file(char *map_file)
{
	int	fd;

	if (!map_file)
		return (-1);
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nCannot open map file\n", 2);
		return (-1);
	}
	return (fd);
}

/*
** Processes map initialization and texture parsing
** Returns: initialized map structure, or NULL on error
*/
static t_map_data	*process_map_data(char *map_file, int fd)
{
	t_map_data	*map;

	map = map_init_from_fd(map_file, fd);
	if (!map)
	{
		ft_putstr_fd("Error\nFailed to initialize map\n", 2);
		return (NULL);
	}
	if (!parse_textures_and_colors(map, map_file))
	{
		ft_putstr_fd("Error\nFailed to parse textures and colors\n", 2);
		map_free(map);
		return (NULL);
	}
	return (map);
}

/**
 * This function receives a map file path and reads the map data.
 * It is expected to parse the map and store it in a suitable data structure.
 */
t_map_data	*map_read(char *map_file)
{
	int			fd;
	t_map_data	*map;

	fd = open_map_file(map_file);
	if (fd < 0)
		return (NULL);
	map = process_map_data(map_file, fd);
	close(fd);
	return (map);
}

/**
 * Frees all memory allocated for a map structure
 */
void	map_free(t_map_data *map)
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
	if (map->north_texture)
		free(map->north_texture);
	if (map->south_texture)
		free(map->south_texture);
	if (map->east_texture)
		free(map->east_texture);
	if (map->west_texture)
		free(map->west_texture);
	free(map);
}
