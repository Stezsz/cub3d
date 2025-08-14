/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:29:51 by tborges-          #+#    #+#             */
/*   Updated: 2025/08/14 16:41:03 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "../includes/libft/libft.h"
# include "../includes/libft/ft_printf/ft_printf.h"
# include "../../includes/libft/get_next_line/get_next_line.h"

typedef struct s_map_data
{
	char	**map;
	int		height;
	int		width;
	char	*north_texture;
	char	*south_texture;
	char	*east_texture;
	char	*west_texture;
	int		floor_color;
	int		ceiling_color;
}	t_map_data;

t_map_data	*map_init_from_fd(char *filename, int fd);
t_map_data	*map_read(char *map_file);
void		map_free(t_map_data *map);
int			map_verify_enclosed(t_map_data *map);
int			map_verify_player_count(t_map_data *map);
int			map_verify_characters(t_map_data *map);
int			map_verify_complete(t_map_data *map);
int			is_walkable(char c);
int			is_wall(char c);
int			is_void(char c);
int			is_valid_char(char c);
int			is_valid_pos(t_map_data *map, int x, int y);
int			check_neighbors_for_void(t_map_data *map, int x, int y);
int			flood_fill_check(t_map_data *map, char **visited, int x, int y);
int			map_find_player_position(t_map_data *map, int *player_x,
				int *player_y);
char		**create_visited_array(t_map_data *map);
void		free_visited_array(char **visited, int height);
int			count_map_lines(int fd);
int			calculate_max_width(char **map_lines, int height);
void		normalize_map_lines(char **map_lines, int height, int width);
int			read_map_lines_from_fd(int fd, char **map_lines, int max_height);
char		**read_map_grid(char *filename, int fd, int *height, int *width);
int			count_map_lines_from_file(char *filename);
int			parse_textures_and_colors(t_map_data *map_data, char *filename);
void		map_print_debug(t_map_data *map);

#endif
