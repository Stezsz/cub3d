/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_textures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 12:00:00 by tborges-          #+#    #+#             */
/*   Updated: 2025/09/01 22:51:52 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

/*
** Validates and calculates color from RGB values
*/
static int	calculate_color(char **rgb)
{
	int	color;

	color = (ft_atoi(rgb[0]) << 16) | (ft_atoi(rgb[1]) << 8) | ft_atoi(rgb[2]);
	if (ft_atoi(rgb[0]) < 0 || ft_atoi(rgb[0]) > 255 || ft_atoi(rgb[1]) < 0
		|| ft_atoi(rgb[1]) > 255 || ft_atoi(rgb[2]) < 0
		|| ft_atoi(rgb[2]) > 255)
		return (-1);
	return (color);
}

/*
** Parses a color string in format "R,G,B" to integer
*/
static int	parse_color_string(char *color_str)
{
	char	**rgb;
	int		color;
	int		i;

	rgb = ft_split(color_str, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		if (rgb)
		{
			i = 0;
			while (rgb[i])
				free(rgb[i++]);
			free(rgb);
		}
		return (-1);
	}
	color = calculate_color(rgb);
	i = 0;
	while (rgb[i])
		free(rgb[i++]);
	free(rgb);
	return (color);
}

/*
** Processes texture and color configuration
*/
static void	process_config_element(t_map_data *map_data, char *trimmed)
{
	if (ft_strncmp(trimmed, "NO ", 3) == 0 && !map_data->north_texture)
		map_data->north_texture = ft_strtrim(trimmed + 3, " \t\n");
	else if (ft_strncmp(trimmed, "SO ", 3) == 0 && !map_data->south_texture)
		map_data->south_texture = ft_strtrim(trimmed + 3, " \t\n");
	else if (ft_strncmp(trimmed, "WE ", 3) == 0 && !map_data->west_texture)
		map_data->west_texture = ft_strtrim(trimmed + 3, " \t\n");
	else if (ft_strncmp(trimmed, "EA ", 3) == 0 && !map_data->east_texture)
		map_data->east_texture = ft_strtrim(trimmed + 3, " \t\n");
	else if (ft_strncmp(trimmed, "F ", 2) == 0 && map_data->floor_color == -1)
		map_data->floor_color = parse_color_string(trimmed + 2);
	else if (ft_strncmp(trimmed, "C ", 2) == 0 && map_data->ceiling_color == -1)
		map_data->ceiling_color = parse_color_string(trimmed + 2);
}

/*
** Processes a texture/color line from the file
*/
static int	process_config_line(t_map_data *map_data, char *line)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, " \t\n");
	if (!trimmed || ft_strlen(trimmed) < 1)
	{
		if (trimmed)
			free(trimmed);
		return (0);
	}
	process_config_element(map_data, trimmed);
	free(trimmed);
	return (1);
}

/**
 * Parses textures and colors from the configuration file
 */
int	parse_textures_and_colors(t_map_data *map_data, char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (is_map_content_line(line))
		{
			free(line);
			break ;
		}
		process_config_line(map_data, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (map_data->north_texture && map_data->south_texture
		&& map_data->east_texture && map_data->west_texture
		&& map_data->floor_color != -1 && map_data->ceiling_color != -1);
}
