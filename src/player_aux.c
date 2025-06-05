/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strodrig <strodrig@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 11:23:54 by tborges-          #+#    #+#             */
/*   Updated: 2025/06/05 16:18:03 by strodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

void	move_player_coordinates(t_player *player, float cos_angle,
		float sin_angle, int speed)
{
	if (player->key_up)
	{
		player->pos.x += cos_angle * speed;
		player->pos.y += sin_angle * speed;
	}
	if (player->key_down)
	{
		player->pos.x -= cos_angle * speed;
		player->pos.y -= sin_angle * speed;
	}
	if (player->key_left)
	{
		player->pos.x += sin_angle * speed;
		player->pos.y -= cos_angle * speed;
	}
	if (player->key_right)
	{
		player->pos.x -= sin_angle * speed;
		player->pos.y += cos_angle * speed;
	}
}
