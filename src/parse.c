/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:00:38 by strodrig          #+#    #+#             */
/*   Updated: 2025/08/13 12:17:11 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


/**
 * Inserts a value into the map_errors structure.
 */
int	insert_value(t_map *errors, char *line, char *check, int i)
{
	int		test;
	int		color_or_texture;
	char	*trim_line;

	color_or_texture = 0;
	while (line[i + color_or_texture] && line[i + color_or_texture] != 32)
		color_or_texture++;
	if (ft_strncmp(line + i, check, color_or_texture) != 0)
		return (EXIT_SUCCESS);
	i += color_or_texture;
	while (line[i] && line[i] == 32)
		i++;
	trim_line = ft_strtrim((line + i), "\n");
	test = open(trim_line, O_RDONLY);
	if (test < 0 && color_or_texture > 1)
		return (free(trim_line), EXIT_FAILURE);
	else if (test > -1)
		close(test);
	if (find_type(errors, trim_line, check))
		return (free(trim_line), EXIT_FAILURE);
	return (free(trim_line), EXIT_SUCCESS);
}


