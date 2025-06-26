/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:19:33 by tborges-          #+#    #+#             */
/*   Updated: 2025/06/26 22:19:53 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	validate_map_walls(char **map)
{
	int	last;

	if (!is_wall_line(map[0]))
		return (false);
	last = 0;
	while (map[last])
		last++;
	if (!is_wall_line(map[last - 1]))
		return (false);
	if (!has_wall_borders(map))
		return (false);
	return (true);
}
