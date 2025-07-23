/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 00:02:13 by tborges-          #+#    #+#             */
/*   Updated: 2025/07/23 22:17:28 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Checks if a line is a wall line.
 * A wall line is defined as a line that contains only '1's and spaces,
 * and at least one '1' must be present.
 */
bool	is_wall_line(const char *line)
{
	int		i;
	bool	found_content;

	i = 0;
	found_content = false;
	while (line[i])
	{
		if (line[i] == '\n')
			break ;
		if (line[i] != '1' && line[i] != ' ')
			return (false);
		if (line[i] == '1')
			found_content = true;
		i++;
	}
	return (found_content);
}

/**
 * Prints the map for debugging purposes.
 */
void	debug_print_map(char **map)
{
	int	i;

	i = 0;
	printf("--- MAP AS READ ---\n");
	while (map[i])
	{
		printf("Line %d: [%s]\n", i, map[i]);
		i++;
	}
	printf("------------------\n");
}
