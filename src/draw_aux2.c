/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_aux2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strodrig <strodrig@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:59:42 by strodrig          #+#    #+#             */
/*   Updated: 2025/06/05 16:59:42 by strodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

float	calculate_wall_hit_x(t_fpoint wall_hit, int wall_side)
{
	t_ipoint	map_pos;
	float		wall_x;

	map_pos.x = wall_hit.x / BLOCK;
	map_pos.y = wall_hit.y / BLOCK;
	if (wall_side == 0 || wall_side == 1)
	{
		wall_x = wall_hit.x - (map_pos.x * BLOCK);
		wall_x = wall_x / BLOCK;
	}
	else
	{
		wall_x = wall_hit.y - (map_pos.y * BLOCK);
		wall_x = wall_x / BLOCK;
	}
	if (wall_x < 0)
		wall_x = 0;
	if (wall_x > 1)
		wall_x = 1;
	return (wall_x);
}

void	draw_white_wall(t_game *game, int i, int wall_start, int wall_end)
{
	int	y;

	y = wall_start;
	while (y < wall_end)
	{
		put_pixel(i, y, 0xFFFFFF, game);
		y++;
	}
}

void	process_ray_casting(t_raycasting *ray_data, t_player *player,
	t_fpoint ray, t_game *game)
{
	float	dist;

	dist = fixed_dist(player->pos, ray, game);
	ray_data->wall_side = determine_wall_side(player->pos, ray);
	ray_data->wall_texture = get_wall_texture(game, ray_data->wall_side);
	ray_data->wall_hit_x = calculate_wall_hit_x(ray, ray_data->wall_side);
	ray_data->wall_height = (BLOCK / dist) * (WIDTH / 2);
	ray_data->wall_start = (HEIGHT - ray_data->wall_height) / 2;
	ray_data->wall_end = ray_data->wall_start + ray_data->wall_height;
	if (ray_data->wall_start < 0)
		ray_data->wall_start = 0;
	if (ray_data->wall_end >= HEIGHT)
		ray_data->wall_end = HEIGHT - 1;
}

void	draw_textured_wall_section(t_game *game, t_raycasting *ray_data, int i)
{
	t_wall_data	wall_data;

	create_floor_ceiling(game, i, ray_data->wall_start, ray_data->wall_end);
	calculate_texture_coordinates(ray_data, game, i);
	wall_data.game = game;
	wall_data.x = i;
	wall_data.wall_start = ray_data->wall_start;
	wall_data.wall_end = ray_data->wall_end;
	wall_data.ray = ray_data;
	if (ray_data->wall_texture && ray_data->wall_texture->data)
		draw_textured_wall(&wall_data);
	else
		draw_white_wall(game, i, ray_data->wall_start, ray_data->wall_end);
}
