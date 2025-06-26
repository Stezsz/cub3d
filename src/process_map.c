/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:07:57 by strodrig          #+#    #+#             */
/*   Updated: 2025/06/26 22:40:04 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	count_map_lines(char *file)
{
	int		fd;
	char	*line;
	int		map_lines;

	map_lines = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ft_strchr(line, '1'))
			map_lines++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (map_lines);
}

static void	read_map_lines(t_map_errors *map_errors, char *file, int map_lines)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return ;
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ft_strchr(line, '1'))
		{
			map_errors->map[i] = ft_strdup(line);
			i++;
		}
		free(line);
		if (i >= map_lines)
			break ;
		line = get_next_line(fd);
	}
	map_errors->map[i] = NULL;
	close(fd);
}

bool	is_wall_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ' && line[i] != '\n')
			return (false);
		i++;
	}
	return (true);
}

bool	has_wall_borders(char **map)
{
	int	i;
	int	len;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] == ' ')
			j++;
		if (map[i][j] != '1')
			return (false);
		len = ft_strlen(map[i]);
		while (len > 0 && (map[i][len - 1] == ' ' || map[i][len - 1] == '\n'))
			len--;
		if (len == 0 || map[i][len - 1] != '1')
			return (false);
		i++;
	}
	return (true);
}

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
		ft_putstr_fd("Error\nNot surrounded by walls\n", 2);
		exit(1);
	}
}
