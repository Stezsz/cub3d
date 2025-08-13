/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_verify_memory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 17:35:00 by tborges-          #+#    #+#             */
/*   Updated: 2025/08/13 17:29:00 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static void	initialize_row(char *row, int width)
{
	int	j;

	j = 0;
	while (j < width)
	{
		row[j] = '0';
		j++;
	}
	row[width] = '\0';
}

/**
 * Creates a visited array for flood fill algorithm
 */
char	**create_visited_array(t_map *map)
{
	char	**visited;
	int		i;

	visited = malloc(sizeof(char *) * map->height);
	if (!visited)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		visited[i] = malloc(sizeof(char) * (map->width + 1));
		if (!visited[i])
		{
			while (--i >= 0)
				free(visited[i]);
			free(visited);
			return (NULL);
		}
		initialize_row(visited[i], map->width);
		i++;
	}
	return (visited);
}

/**
 * Frees the visited array
 */
void	free_visited_array(char **visited, int height)
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
