/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:30:00 by tborges-          #+#    #+#             */
/*   Updated: 2025/09/01 22:50:20 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "map.h"
#include <stdio.h>

/*
** Debug function to print the map
*/
void	map_print_debug(t_map_data *map)
{
	int	i;

	if (!map || !map->map)
	{
		printf("Map is NULL or invalid\n");
		return ;
	}
	printf("Map dimensions: %dx%d\n", map->width, map->height);
	printf("North texture: %s\n", map->north_texture ? map->north_texture : "NULL");
	printf("South texture: %s\n", map->south_texture ? map->south_texture : "NULL");
	printf("East texture: %s\n", map->east_texture ? map->east_texture : "NULL");
	printf("West texture: %s\n", map->west_texture ? map->west_texture : "NULL");
	printf("Floor color: %d\n", map->floor_color);
	printf("Ceiling color: %d\n", map->ceiling_color);
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

/*
** Test program to demonstrate map initialization
** Usage: ./test_map <map_file>
*/
int	main(int argc, char **argv)
{
	t_map_data	*map;

	if (argc != 2)
	{
		printf("Usage: %s <map_file>\n", argv[0]);
		return (1);
	}
	printf("Loading map from: %s\n", argv[1]);
	map = map_read(argv[1]);
	if (!map)
	{
		printf("Failed to load map!\n");
		return (1);
	}
	map_print_debug(map);
	printf("\nCharacter verification: ");
	if (map_verify_characters(map))
		printf("PASSED - All characters are valid\n");
	else
		printf("FAILED - Invalid characters found\n");
	printf("Enclosure verification: ");
	if (map_verify_enclosed(map))
		printf("PASSED - Map is properly enclosed by walls\n");
	else
		printf("FAILED - Map has openings to void spaces\n");
	printf("\nComplete verification: ");
	if (map_verify_complete(map))
		printf("PASSED - Map is fully valid\n");
	else
		printf("FAILED - Map has validation errors\n");
	map_free(map);
	return (0);
}
