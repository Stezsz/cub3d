/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:00:00 by tborges-          #+#    #+#             */
/*   Updated: 2025/08/13 19:10:21 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

/**
 * Counts the number of map lines in the file
 */
int	count_map_lines(int fd)
{
	char	*line;
	int		count;
	int		found_map_start;

	count = 0;
	found_map_start = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!found_map_start && (line[0] == ' ' || line[0] == '1'))
			found_map_start = 1;
		if (found_map_start)
		{
			if (line[0] == '\n' || line[0] == '\0')
				break ;
			count++;
		}
		free(line);
		line = get_next_line(fd);
	}
	return (count);
}

/**
 * Calculates the maximum width of the map
 */
int	calculate_max_width(char **map_lines, int height)
{
	int	len;
	int	max_width;
	int	i;

	max_width = 0;
	i = 0;
	while (i < height)
	{
		len = ft_strlen(map_lines[i]);
		if (len > 0 && map_lines[i][len - 1] == '\n')
			len--;
		if (len > max_width)
			max_width = len;
		i++;
	}
	return (max_width);
}

/**
 * Normalizes a single map line to have the proper width
 */
static void	normalize_single_line(char **map_line, int old_len, int width)
{
	char	*old_line;
	int		j;

	old_line = *map_line;
	*map_line = malloc(width + 1);
	if (!*map_line)
	{
		free(old_line);
		return ;
	}
	j = 0;
	while (j < old_len)
	{
		(*map_line)[j] = old_line[j];
		j++;
	}
	while (j < width)
	{
		(*map_line)[j] = ' ';
		j++;
	}
	(*map_line)[width] = '\0';
	free(old_line);
}

/**
 * Normalizes map lines to have the same width (pad with spaces)
 */
void	normalize_map_lines(char **map_lines, int height, int width)
{
	int	i;
	int	old_len;

	i = 0;
	while (i < height)
	{
		old_len = ft_strlen(map_lines[i]);
		if (old_len > 0 && map_lines[i][old_len - 1] == '\n')
		{
			map_lines[i][old_len - 1] = '\0';
			old_len--;
		}
		if (old_len < width)
			normalize_single_line(&map_lines[i], old_len, width);
		i++;
	}
}
