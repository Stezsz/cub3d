/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 22:10:58 by tborges-          #+#    #+#             */
/*   Updated: 2025/08/14 15:17:02 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Initializes MLX resources and creates window and image.
*/
static void	init_mlx_resources(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3d");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line,
			&game->endian);
}

/*
** Creates a t_map structure from t_map_data for texture loading compatibility
*/
static t_map	*create_parsed_map(t_map_data *map_data)
{
	t_map	*parsed;

	parsed = malloc(sizeof(t_map));
	if (!parsed)
		return (NULL);
	ft_bzero(parsed, sizeof(t_map));
	parsed->north_texture = ft_strdup(map_data->north_texture);
	parsed->south_texture = ft_strdup(map_data->south_texture);
	parsed->east_texture = ft_strdup(map_data->east_texture);
	parsed->west_texture = ft_strdup(map_data->west_texture);
	parsed->floor_color = map_data->floor_color;
	parsed->ceiling_color = map_data->ceiling_color;
	parsed->map = map_data->map;
	return (parsed);
}

/*
** Helper function to handle map data loading and verification
*/
static t_map_data	*load_and_verify_map(char *map_path)
{
	t_map_data	*map_data;

	ft_printf("Loading map from: %s\n", map_path);
	map_data = map_read(map_path);
	if (!map_data)
	{
		ft_putstr_fd("Error\nLoading map failed.\n", 2);
		exit(1);
	}
	ft_printf("Map loaded successfully - dimensions: %dx%d\n",
		map_data->width, map_data->height);
	if (!map_verify_complete(map_data))
	{
		ft_putstr_fd("Error\nInvalid Map!\n", 2);
		map_free(map_data);
		exit(1);
	}
	ft_printf("Map verification passed\n");
	return (map_data);
}

/*
** Initializes the game structure and loads the map and textures.
*/
static void	init_game(t_game *game, char *map_path)
{
	t_map_data	*map_data;

	map_data = load_and_verify_map(map_path);
	game->map = map_data->map;
	game->map_data = map_data;
	game->parsed = create_parsed_map(map_data);
	if (!game->parsed)
	{
		ft_putstr_fd("Error\nFailed to create parsed map structure.\n", 2);
		map_free(map_data);
		exit(1);
	}
	if (!init_player_from_map(game))
	{
		map_free(map_data);
		exit(1);
	}
	ft_printf("Player initialized\n");
	init_mlx_resources(game);
	ft_printf("MLX initialized\n");
	load_textures(game, game->parsed);
	ft_printf("Textures loaded\n");
}

/*
** Main function to initialize the game and start the event loop.
*/
int	main(int ac, char **av)
{
	t_game	game;

	ft_bzero(&game, sizeof(t_game));
	if (ac != 2)
	{
		ft_putstr_fd("Usage: ./cub3d <map_file>\n", 2);
		return (1);
	}
	init_game(&game, av[1]);
	if (!game.map)
		return (1);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game.player);
	mlx_hook(game.win, 17, 0, close_game, &game);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
