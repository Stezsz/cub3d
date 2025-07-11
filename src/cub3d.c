/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 22:10:58 by tborges-          #+#    #+#             */
/*   Updated: 2025/07/11 21:45:00 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_game(t_game *game, char *map_path)
{
	t_map_errors	*parse_result;

	parse_result = parse_map(map_path);
	if (!parse_result)
	{
		ft_putstr_fd("Erro ao fazer o parsing do mapa.\n", 2);
		exit(1);
	}
	game->map = parse_result->map;
	if (!game->map)
	{
		ft_putstr_fd("Erro ao carregar o mapa.\n", 2);
		free(parse_result);
		exit(1);
	}
	init_player_from_map(&game->player, game->map);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Game");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line,
			&game->endian);
	game->parsed = parse_result;
	load_textures(game, parse_result);
	ft_bzero(game->data, HEIGHT * game->size_line);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
	{
		ft_putstr_fd("Usage: ./cub3d <map_file>\n", 2);
		return (1);
	}
	init_game(&game, av[1]);
	if (!game.map)
		return (1);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game.player);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game.player);
	mlx_hook(game.win, 17, 0, close_game, &game);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
