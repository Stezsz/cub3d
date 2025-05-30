/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 22:10:58 by tborges-          #+#    #+#             */
/*   Updated: 2025/05/29 19:59:16 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;             // Blue
	game->data[index + 1] = (color >> 8) & 0xFF;  // Green
	game->data[index + 2] = (color >> 16) & 0xFF; // Red
}

void	draw_square(int x, int y, int size, int color, t_game *game)
{
	for (int i = 0; i < size; i++)
		put_pixel(x, y + i, color, game);
	for (int i = 0; i < size; i++)
		put_pixel(x + i, y, color, game);
	for (int i = 0; i < size; i++)
		put_pixel(x + size, y + i, color, game);
	for (int i = 0; i < size; i++)
		put_pixel(x + i, y + size, color, game);
}

void	clear_image(t_game *game)
{
	int x, y;
	for (y = 0; y < HEIGHT; y++)
		for (x = 0; x < WIDTH; x++)
			put_pixel(x, y, 0x000000, game);
}

void	init_game(t_game *game)
{
	init_player(&game->player);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Game");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line,
			&game->endian);
	// mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

int	draw_loop(t_game *game)
{
	t_player	*player;

	player = &game->player;
	clear_image(game); // Limpa a imagem antes de desenhar
	// move_player(player);
	draw_square(player->x, player->y, 5, 0xFF0000, game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

int	main(void)
{
	t_game	game;

	init_game(&game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
