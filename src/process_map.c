/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strodrig <strodrig@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:07:57 by strodrig          #+#    #+#             */
/*   Updated: 2025/07/26 14:04:14 by strodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Counts the number of lines in the map file.
 */
static int	count_map_lines(char *file)
{
	int		fd;
	char	*line;
	int		map_lines;
	bool	map_started;

	map_started = false;
	map_lines = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line[0] == '1' || (line[0] == ' ' && ft_strchr(line, '1')))
			map_started = true;
		if (map_started && (line[0] == '1' || line[0] == ' '
				|| ft_strchr("NSEW", line[0]) || line[0] == '0'))
			map_lines++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (map_lines);
}

/**
 * Reads the map lines from the file and stores them in the map_errors structure.
 */
static void	read_map_lines_aux(char *line, t_map_errors *map_errors, int *i,
		bool *map_started)
{
	if (line[0] == '1' || (line[0] == ' ' && ft_strchr(line, '1')))
		*map_started = true;
	if (*map_started && (line[0] == '1' || line[0] == ' ' || ft_strchr("NSEW",
				line[0]) || line[0] == '0'))
	{
		map_errors->map[*i] = ft_strdup(line);
		(*i)++;
	}
}

/**
 * Reads the map lines from the file and stores them in the map_errors structure.
 */
static void	read_map_lines(t_map_errors *map_errors, char *file, int map_lines)
{
	int		fd;
	char	*line;
	int		i;
	bool	map_started;

	map_started = false;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return ;
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		read_map_lines_aux(line, map_errors, &i, &map_started);
		free(line);
		if (i >= map_lines)
			break ;
		line = get_next_line(fd);
	}
	map_errors->map[i] = NULL;
	close(fd);
}

/**
 * Processes the map by reading its lines and validating its structure.
 */
void	process_map(t_map_errors *map_errors, char *file)
{
	int	map_lines;

	map_lines = count_map_lines(file);
	if (map_lines == 0)
		return ;
	map_errors->map = malloc(sizeof(char *) * (map_lines + 1));
	if (!map_errors->map)
		return ;
	read_map_lines(map_errors, file, map_lines);
	if (!validate_map_walls(map_errors->map))
	{
		ft_putstr_fd("Error\nMap not surrounded by walls\n", 2);
		exit(1);
	}
}
