/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:29:51 by tborges-          #+#    #+#             */
/*   Updated: 2025/08/13 19:10:21 by tborges-         ###   ########.fr       */
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

typedef struct s_map
{
	char	**map;
	int		height;
	int		width;
}	t_map;

// Function prototypes
t_map	*map_init_from_fd(int fd);
t_map	*map_read(char *map_file);
void	map_free(t_map *map);
void	map_print_debug(t_map *map);

// Map verification functions
int		map_verify_enclosed(t_map *map);
int		map_verify_player_count(t_map *map);
int		map_verify_characters(t_map *map);
int		map_verify_complete(t_map *map);

// map_verify_utils.c
int		is_walkable(char c);
int		is_wall(char c);
int		is_void(char c);
int		is_valid_char(char c);
int		is_valid_pos(t_map *map, int x, int y);

// map_verify_aux.c
int		check_neighbors_for_void(t_map *map, int x, int y);
int		flood_fill_check(t_map *map, char **visited, int x, int y);
int		find_player_position(t_map *map, int *player_x, int *player_y);

// map_verify_memory.c
char	**create_visited_array(t_map *map);
void	free_visited_array(char **visited, int height);

// map_read_utils.c
int		count_map_lines(int fd);
int		calculate_max_width(char **map_lines, int height);
void	normalize_map_lines(char **map_lines, int height, int width);

// map_read_grid.c
int		read_map_lines_from_fd(int fd, char **map_lines, int max_height);
char	**read_map_grid(int fd, int *height, int *width);

#endif
