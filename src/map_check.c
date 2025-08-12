/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:53:39 by tborges-          #+#    #+#             */
/*   Updated: 2025/08/12 12:43:00 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	**alloc_int_matrix(int rows, int cols)
{
	int	**m;
	int	i;
	int	j;

	m = malloc(sizeof(int *) * rows);
	if (!m)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		m[i] = malloc(sizeof(int) * cols);
		if (!m[i])
			return (NULL);
		j = 0;
		while (j < cols)
			m[i][j++] = 0;
		i++;
	}
	return (m);
}

static void	normalize_map(char **map, int rows, int cols)
{
	int		i;
	size_t	len;
	int		j;

	i = 0;
	while (i < rows)
	{
		len = ft_strlen(map[i]);
		if ((int)len < cols)
		{
			map[i] = realloc(map[i], cols + 1);
			j = len;
			while (j < cols)
				map[i][j++] = ' ';
			map[i][cols] = '\0';
		}
		i++;
	}
}

static int	is_invalid_cell(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

static int	flood_fill(char **map, int **vis, int r, int c, int x, int y)
{
	if (x < 0 || y < 0 || x >= r || y >= c)
		return (0);
	if (vis[x][y] || map[x][y] == '1')
		return (1);
	vis[x][y] = 1;
	if (is_invalid_cell(map[x][y]))
		return (0);
	if (!flood_fill(map, vis, r, c, x + 1, y)
		|| !flood_fill(map, vis, r, c, x - 1, y)
		|| !flood_fill(map, vis, r, c, x, y + 1)
		|| !flood_fill(map, vis, r, c, x, y - 1))
		return (0);
	return (1);
}

int	check_closed_map(char **map, int rows, int cols)
{
	int	**vis;
	int	i;
	int	j;

	normalize_map(map, rows, cols);
	vis = alloc_int_matrix(rows, cols);
	if (!vis)
		return (0);
	i = 0;
	while (i < rows)
	{
		if (!flood_fill(map, vis, rows, cols, i, 0)
			|| !flood_fill(map, vis, rows, cols, i, cols - 1))
			return (0);
		i++;
	}
	j = 0;
	while (j < cols)
	{
		if (!flood_fill(map, vis, rows, cols, 0, j)
			|| !flood_fill(map, vis, rows, cols, rows - 1, j))
			return (0);
		j++;
	}
	return (1);
}
