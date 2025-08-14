/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lseek.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 11:44:32 by tborges-          #+#    #+#             */
/*   Updated: 2025/08/14 11:50:03 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

/**
 * Processes a line during map counting
 */
static int	process_count_line(char *line, int *found_map_start, int *count)
{
	if (!(*found_map_start) && (line[0] == ' ' || line[0] == '1'))
		*found_map_start = 1;
	if (*found_map_start)
	{
		if (line[0] == '\n' || line[0] == '\0')
			return (-1);
		(*count)++;
	}
	return (0);
}

/**
 * Counts map lines by opening a separate file descriptor
 * This avoids the need for lseek by using a temporary fd
 */
int	count_map_lines_from_file(char *filename)
{
	int		fd;
	int		count;
	char	*line;
	int		found_map_start;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	count = 0;
	found_map_start = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (process_count_line(line, &found_map_start, &count) == -1)
		{
			free(line);
			break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}
