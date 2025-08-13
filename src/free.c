/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:06:20 by strodrig          #+#    #+#             */
/*   Updated: 2025/08/13 12:17:11 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Frees the memory allocated for the parsed textures.
 */
static void	free_parsed_textures(t_map *parsed)
{
	if (parsed->north_texture)
		free(parsed->north_texture);
	if (parsed->south_texture)
		free(parsed->south_texture);
	if (parsed->east_texture)
		free(parsed->east_texture);
	if (parsed->west_texture)
		free(parsed->west_texture);
	if (parsed->line_of_map)
		free(parsed->line_of_map);
}

/**
 * Cleans up the parsed data in the game structure.
 */
static void	cleanup_parsed(t_game *game)
{
	if (game->parsed)
	{
		free_parsed_textures(game->parsed);
		free(game->parsed);
	}
}

/**
 * Cleans up the MLX resources in the game structure.
 */
static void	cleanup_mlx_resources(t_game *game)
{
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

/**
 * Closes the game and frees all resources.
 */
int	close_game(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (game)
	{
		destroy_textures(game);
		free_map(game->map);
		cleanup_parsed(game);
		cleanup_mlx_resources(game);
	}
	exit(0);
	return (0);
}

/**
 * Frees the memory allocated for the game map.
 */
void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}
