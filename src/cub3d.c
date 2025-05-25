/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 22:10:58 by tborges-          #+#    #+#             */
/*   Updated: 2025/05/25 23:42:20 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void put_pixel(int x, int y, int color, t_game *game)
{
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	int index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF; // Blue
	game->data[index + 1] = (color >> 8) & 0xFF; // Green
	game->data[index + 2] = (color >> 16) & 0xFF; // Red
}

void draw_square(int x, int y, int size, int color, t_game *game)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			put_pixel(x + j, y + i, color, game);
		}
	}
}

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Game");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
}

int main(void)
{
	t_game game;

	init_game(&game);
	// draw_square(WIDTH / 2, HEIGHT / 2, 10, 0xFF0000, &game); // Draw a red square at (100, 100) with size 50
	mlx_loop(game.mlx);

	return (0);
}
