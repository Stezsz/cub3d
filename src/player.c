/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:08:43 by tborges-          #+#    #+#             */
/*   Updated: 2025/07/11 22:13:52 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_release(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = false;
	else if (keycode == S)
		player->key_down = false;
	else if (keycode == A)
		player->key_left = false;
	else if (keycode == D)
		player->key_right = false;
	else if (keycode == LEFT)
		player->left_rotate = false;
	else if (keycode == RIGHT)
		player->right_rotate = false;
	return (0);
}

void	move_player(t_player *player, t_game *game)
{
	int				speed;
	float			angle_speed;
	t_move_params	params;

	speed = 3;
	angle_speed = 0.03;
	params.cos_angle = cos(player->angle);
	params.sin_angle = sin(player->angle);
	params.speed = speed;
	move_player_angle(player, angle_speed);
	move_player_coordinates(player, params, game);
}

int	key_press(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = true;
	else if (keycode == S)
		player->key_down = true;
	else if (keycode == A)
		player->key_left = true;
	else if (keycode == D)
		player->key_right = true;
	else if (keycode == LEFT)
		player->left_rotate = true;
	else if (keycode == RIGHT)
		player->right_rotate = true;
	else if (keycode == 65307)
		exit(0);
	return (0);
}

void	move_player_angle(t_player *player, float angle_speed)
{
	if (player->left_rotate)
		player->angle -= angle_speed;
	if (player->right_rotate)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
}
