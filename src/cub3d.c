/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strodrig <strodrig@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 22:10:58 by tborges-          #+#    #+#             */
/*   Updated: 2025/06/04 12:32:16 by strodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	**get_map(void)
{
	char	**map;

	map = malloc(sizeof(char *) * 11);
	map[0] = ft_strdup("111111111111111");
	map[1] = ft_strdup("100000000000001");
	map[2] = ft_strdup("100000000000001");
	map[3] = ft_strdup("100000100000001");
	map[4] = ft_strdup("100000000000001");
	map[5] = ft_strdup("100000010000001");
	map[6] = ft_strdup("100001000000001");
	map[7] = ft_strdup("100000000000001");
	map[8] = ft_strdup("100000000000001");
	map[9] = ft_strdup("111111111111111");
	map[10] = NULL;
	return (map);
}

void	init_game(t_game *game)
{
	init_player(&game->player);
	game->map = get_map();
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Game");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line,
			&game->endian);
	ft_bzero(game->data, HEIGHT * game->size_line);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

int	main(void)
{
	t_game	game;

	init_game(&game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game.player);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game.player);
	mlx_hook(game.win, 17, 0, close_game, &game);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
