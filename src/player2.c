/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 21:47:29 by tborges-          #+#    #+#             */
/*   Updated: 2025/07/23 22:06:26 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Sets the player's angle based on the direction character.
 */
static void	set_player_angle_from_direction(t_player *player, char direction)
{
	if (direction == 'N')
		player->angle = 3 * PI / 2;
	else if (direction == 'S')
		player->angle = PI / 2;
	else if (direction == 'E')
		player->angle = 0;
	else if (direction == 'W')
		player->angle = PI;
	else
		player->angle = PI / 2;
}

/**
 * Initializes the player's key states.
 */
static void	init_player_keys(t_player *player)
{
	player->key_up = false;
	player->key_down = false;
	player->key_right = false;
	player->key_left = false;
	player->left_rotate = false;
	player->right_rotate = false;
}

/**
 * Initializes the player's position to the default values.
 */
static void	init_player_pos_default(t_player *player)
{
	player->pos.x = WIDTH / 2;
	player->pos.y = HEIGHT / 2;
	player->angle = PI / 2;
}

/**
 * Initializes the player's position to the specified values.
 */
static void	init_player_pos(t_player *player, int x, int y)
{
	player->pos.x = x * BLOCK + BLOCK / 2;
	player->pos.y = y * BLOCK + BLOCK / 2;
}

/**
 * Initializes the player from the map.
 * It searches for the player's starting position
 * and sets the angle based on the direction character found.
 */
void	init_player_from_map(t_player *player, char **map)
{
	int		x;
	int		y;
	char	direction;

	init_player_keys(player);
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E'
				|| map[y][x] == 'W')
			{
				direction = map[y][x];
				init_player_pos(player, x, y);
				set_player_angle_from_direction(player, direction);
				map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
	init_player_pos_default(player);
}
