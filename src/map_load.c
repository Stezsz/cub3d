/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 12:48:47 by tborges-          #+#    #+#             */
/*   Updated: 2025/08/12 12:49:01 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"

static int	is_map_line(char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	if (s[i] == '1' || s[i] == '0'
		|| s[i] == 'N' || s[i] == 'S'
		|| s[i] == 'E' || s[i] == 'W')
		return (1);
	return (0);
}

static char	*dup_line(char *s)
{
	int		len;
	char	*new;
	int		i;

	len = 0;
	while (s[len])
		len++;
	new = malloc(len + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new[i] = s[i];
		i++;
	}
	new[len] = '\0';
	return (new);
}

static void	count_map_size(char *file, int *h, int *w)
{
	int		fd;
	char	*line;
	int		len;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return ;
	*h = 0;
	*w = 0;
	while ((line = get_next_line(fd)))
	{
		if (is_map_line(line))
		{
			len = 0;
			while (line[len] && line[len] != '\n')
				len++;
			if (len > *w)
				*w = len;
			(*h)++;
		}
		free(line);
	}
	close(fd);
}

static char	**load_map(char *file, int h)
{
	int		fd;
	char	*line;
	char	**map;
	int		i;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = malloc(sizeof(char *) * (h + 1));
	if (!map)
		return (NULL);
	i = 0;
	while ((line = get_next_line(fd)))
	{
		if (is_map_line(line))
			map[i++] = dup_line(line);
		free(line);
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

char	**get_map_from_file(char *file, int *h, int *w)
{
	char	**map;

	count_map_size(file, h, w);
	map = load_map(file, *h);
	return (map);
}
