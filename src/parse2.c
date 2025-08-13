/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:34:13 by strodrig          #+#    #+#             */
/*   Updated: 2025/08/13 12:17:11 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Checks the type of the line and inserts the corresponding file or color.
 */
int	find_type(t_map *errors, char *trim_line, char *check)
{
	if (ft_strncmp(check, "NO", 3) == 0)
		inset_file(&errors->inv_north, &errors->north_texture, trim_line);
	else if (ft_strncmp(check, "SO", 3) == 0)
		inset_file(&errors->inv_south, &errors->south_texture, trim_line);
	else if (ft_strncmp(check, "WE", 3) == 0)
		inset_file(&errors->inv_west, &errors->west_texture, trim_line);
	else if (ft_strncmp(check, "EA", 3) == 0)
		inset_file(&errors->inv_east, &errors->east_texture, trim_line);
	else if (ft_strncmp(check, "F", 2) == 0)
		inset_color(&errors->inv_floor, &errors->floor_color, trim_line);
	else if (ft_strncmp(check, "C", 2) == 0)
		inset_color(&errors->inv_ceiling, &errors->ceiling_color, trim_line);
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * Inserts the file path into the corresponding texture pointer.
 * Increments the counter for the number of textures found.
 */
void	inset_file(int *add_direc, char **dest, char*origin)
{
	*add_direc += 1;
	*dest = ft_strdup(origin);
}

/**
 * Finds the color value from the given string.
 */
int	find_color(char *origin, int i, int *grand_total)
{
	int	total;

	total = 0;
	while (origin[i])
	{
		while (origin[i] && origin[i] != ',')
		{
			if (!ft_isdigit(origin[i]))
				return (EXIT_FAILURE);
			total *= 10;
			total += origin[i] - 48;
			i++;
		}
		if (total > 255)
			return (EXIT_FAILURE);
		*grand_total *= 256;
		*grand_total += total;
		total = 0;
		if (!origin[i])
			break ;
		i++;
	}
	return (EXIT_SUCCESS);
}

/**
 * Inserts the color value into the corresponding color pointer.
 * Increments the counter for the number of colors found.
 */
void	inset_color(int *add_color, int *dest, char*origin)
{
	int	i;
	int	grand_total;

	i = 0;
	grand_total = 0;
	if (find_color(origin, i, &grand_total) == EXIT_FAILURE)
		return ;
	*add_color += 1;
	*dest = grand_total;
}
