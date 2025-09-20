/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:11:02 by strodrig          #+#    #+#             */
/*   Updated: 2025/09/20 13:46:33 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Loads a single texture from a file.
 */
static void	load_single_texture(t_game *g, t_texture *texture,
		char *texture_path, char *error_msg)
{
	texture->img = mlx_xpm_file_to_image(g->mlx, texture_path,
			&texture->width, &texture->height);
	if (texture->img)
		texture->data = mlx_get_data_addr(texture->img,
				&texture->bpp, &texture->size_line, &texture->endian);
	else
		ft_putstr_fd(error_msg, 2);
}

/**
 * Loads all wall textures from the parsed map.
 */
void	load_wall_textures(t_game *g, t_map *parsed)
{
	load_single_texture(g, g->textures->north, parsed->north_texture,
		"Warning: Failed to load north texture\n");
	load_single_texture(g, g->textures->south, parsed->south_texture,
		"Warning: Failed to load south texture\n");
	load_single_texture(g, g->textures->east, parsed->east_texture,
		"Warning: Failed to load east texture\n");
	load_single_texture(g, g->textures->west, parsed->west_texture,
		"Warning: Failed to load west texture\n");
}
