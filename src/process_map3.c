/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 00:02:13 by tborges-          #+#    #+#             */
/*   Updated: 2025/07/09 00:02:38 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	is_wall_line(const char *line)
{
	int		i;
	bool	found_content;

	i = 0;
	found_content = false;
	while (line[i])
	{
		if (line[i] == '\n')
			break ;
		if (line[i] != '1' && line[i] != ' ')
			return (false);
		if (line[i] == '1')
			found_content = true;
		i++;
	}
	return (found_content);
}

void	debug_print_map(char **map)
{
	int	i;

	i = 0;
	printf("--- MAP AS READ ---\n");
	while (map[i])
	{
		printf("Line %d: [%s]\n", i, map[i]);
		i++;
	}
	printf("------------------\n");
}
