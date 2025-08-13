/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:30:00 by tborges-          #+#    #+#             */
/*   Updated: 2025/08/13 18:03:58 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <stdio.h>

/**
 * Test program to demonstrate map initialization
 * Usage: ./test_map <map_file>
 */
int main(int argc, char **argv)
{
	t_map *map;

	if (argc != 2)
	{
		printf("Usage: %s <map_file>\n", argv[0]);
		return (1);
	}

	printf("Loading map from: %s\n", argv[1]);

	// Initialize map from file
	map = map_read(argv[1]);
	if (!map)
	{
		printf("Failed to load map!\n");
		return (1);
	}

	// Print map information and content
	map_print_debug(map);

	// Check character validity
	printf("\nCharacter verification: ");
	if (map_verify_characters(map))
		printf("PASSED - All characters are valid\n");
	else
		printf("FAILED - Invalid characters found\n");

	// Verify if map is properly enclosed
	printf("Enclosure verification: ");
	if (map_verify_enclosed(map))
		printf("PASSED - Map is properly enclosed by walls\n");
	else
		printf("FAILED - Map has openings to void spaces\n");

	// Complete verification (characters + enclosure + player count)
	printf("\nComplete verification: ");
	if (map_verify_complete(map))
		printf("PASSED - Map is fully valid\n");
	else
		printf("FAILED - Map has validation errors\n");

	// Clean up
	map_free(map);	return (0);
}
