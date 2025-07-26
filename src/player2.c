/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 21:47:29 by tborges-          #+#    #+#             */
/*   Updated: 2025/07/26 16:00:03 by tborges-         ###   ########.fr       */
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
 * Initializes the player's position to the specified values.
 */
static void	init_player_pos(t_player *player, int x, int y)
{
	player->pos.x = x * BLOCK + BLOCK / 2;
	player->pos.y = y * BLOCK + BLOCK / 2;
}

/**
 * Finds the player's starting position in the map.
 * Returns the direction character found, or 0 if not found.
 */
static char	find_player_position(char **map, int *player_x, int *player_y)
{
	int		x;
	int		y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E'
				|| map[y][x] == 'W')
			{
				*player_x = x;
				*player_y = y;
				return (map[y][x]);
			}
			x++;
		}
		y++;
	}
	return (0);
}

/**
 * Initializes the player from the map.
 * It searches for the player's starting position
 * and sets the angle based on the direction character found.
 * Returns true if successful, false if player not found.
 */
bool	init_player_from_map(t_game *game)
{
	t_player	*player;
	char		direction;
	int			player_x;
	int			player_y;

	player = &game->player;
	init_player_keys(player);
	direction = find_player_position(game->map, &player_x, &player_y);
	if (direction == 0)
	{
		ft_putstr_fd("Error\nPlayer not found in map.\n", 2);
		return (false);
	}
	init_player_pos(player, player_x, player_y);
	set_player_angle_from_direction(player, direction);
	game->map[player_y][player_x] = '0';
	return (true);
}
