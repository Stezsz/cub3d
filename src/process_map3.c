/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 00:02:13 by tborges-          #+#    #+#             */
/*   Updated: 2025/08/12 12:35:29 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
