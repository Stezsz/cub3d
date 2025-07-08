/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:00:38 by strodrig          #+#    #+#             */
/*   Updated: 2025/07/09 00:21:14 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_map_errors	*init_parser(void)
{
	t_map_errors	*map_errors;

	map_errors = (t_map_errors *)ft_calloc(1, sizeof(t_map_errors));
	if (!map_errors)
		return (NULL);
	map_errors->inv_north = -1;
	map_errors->inv_south = -1;
	map_errors->inv_west = -1;
	map_errors->inv_east = -1;
	map_errors->inv_floor = -1;
	map_errors->inv_ceiling = -1;
	map_errors->north_texture = NULL;
	map_errors->south_texture = NULL;
	map_errors->west_texture = NULL;
	map_errors->east_texture = NULL;
	map_errors->map = NULL;
	return (map_errors);
}

int	insert_value(t_map_errors *errors, char *line, char *check, int i)
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

int	line_check(char **line, t_map_errors *map_errors)
{
	int	i;

	if (*line)
		free(*line);
	*line = get_next_line(map_errors->current_fd);
	if (!(*line))
		return (EXIT_FAILURE);
	i = 0;
	while ((*line)[i] && ((*line)[i] == 32 || (*line)[i] == '\t'))
		i++;
	if ((*line)[i] == '\n' || (*line)[i] == '\0' ||
		(ft_strncmp(*line + i, "NO ", 3) == 0 &&
		insert_value(map_errors, *line, "NO", i) != EXIT_FAILURE) ||
		(ft_strncmp(*line + i, "SO ", 3) == 0 &&
		insert_value(map_errors, *line, "SO", i) != EXIT_FAILURE) ||
		(ft_strncmp(*line + i, "WE ", 3) == 0 &&
		insert_value(map_errors, *line, "WE", i) != EXIT_FAILURE) ||
		(ft_strncmp(*line + i, "EA ", 3) == 0 &&
		insert_value(map_errors, *line, "EA", i) != EXIT_FAILURE) ||
		(ft_strncmp(*line + i, "F ", 2) == 0 &&
		insert_value(map_errors, *line, "F", i) != EXIT_FAILURE) ||
		(ft_strncmp(*line + i, "C ", 2) == 0 &&
		insert_value(map_errors, *line, "C", i) != EXIT_FAILURE))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

t_map_errors	*parse_map(char *file)
{
	char			*line;
	t_map_errors	*map_errors;

	line = NULL;
	map_errors = init_parser();
	if (!map_errors)
		return (NULL);
	map_errors->current_fd = open(file, O_RDONLY);
	if (map_errors->current_fd < 0)
	{
		free(map_errors);
		perror("Error\nFile not found");
		exit(EXIT_FAILURE);
	}
	while (1)
		if (line_check(&line, map_errors) == EXIT_FAILURE)
			break ;
	map_errors->line_of_map = line;
	process_map(map_errors, file);
	close(map_errors->current_fd);
	return (map_errors);
}
