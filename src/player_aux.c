/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 11:23:54 by tborges-          #+#    #+#             */
/*   Updated: 2025/07/11 22:13:48 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	is_valid_position(t_fpoint new_pos, t_game *game)
{
	return (!touch(new_pos, game));
}

static void	try_move_forward(t_player *player, t_move_params params,
		t_game *game)
{
	t_fpoint	new_pos;

	if (player->key_up)
	{
		new_pos.x = player->pos.x + params.cos_angle * params.speed;
		new_pos.y = player->pos.y + params.sin_angle * params.speed;
		if (is_valid_position(new_pos, game))
		{
			player->pos.x = new_pos.x;
			player->pos.y = new_pos.y;
		}
	}
}

static void	try_move_backward(t_player *player, t_move_params params,
		t_game *game)
{
	t_fpoint	new_pos;

	if (player->key_down)
	{
		new_pos.x = player->pos.x - params.cos_angle * params.speed;
		new_pos.y = player->pos.y - params.sin_angle * params.speed;
		if (is_valid_position(new_pos, game))
		{
			player->pos.x = new_pos.x;
			player->pos.y = new_pos.y;
		}
	}
}

static void	try_move_sideways(t_player *player, t_move_params params,
		t_game *game)
{
	t_fpoint	new_pos;

	if (player->key_left)
	{
		new_pos.x = player->pos.x + params.sin_angle * params.speed;
		new_pos.y = player->pos.y - params.cos_angle * params.speed;
		if (is_valid_position(new_pos, game))
		{
			player->pos.x = new_pos.x;
			player->pos.y = new_pos.y;
		}
	}
	if (player->key_right)
	{
		new_pos.x = player->pos.x - params.sin_angle * params.speed;
		new_pos.y = player->pos.y + params.cos_angle * params.speed;
		if (is_valid_position(new_pos, game))
		{
			player->pos.x = new_pos.x;
			player->pos.y = new_pos.y;
		}
	}
}

void	move_player_coordinates(t_player *player, t_move_params params,
		t_game *game)
{
	try_move_forward(player, params, game);
	try_move_backward(player, params, game);
	try_move_sideways(player, params, game);
}
