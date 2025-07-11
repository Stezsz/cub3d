/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:06:20 by strodrig          #+#    #+#             */
/*   Updated: 2025/07/11 21:48:18 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	free_parsed_textures(t_map_errors *parsed)
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

static void	cleanup_parsed(t_game *game)
{
	if (game->parsed)
	{
		free_parsed_textures(game->parsed);
		free(game->parsed);
	}
}

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
