/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:08:59 by strodrig          #+#    #+#             */
/*   Updated: 2025/08/13 12:17:11 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Initializes the textures structure in the game.
 * Allocates memory for the textures and initializes them.
 */
void	init_textures(t_game *g)
{
	g->textures = malloc(sizeof(t_textures));
	if (!g->textures)
	{
		ft_putstr_fd("Error\nFailed to allocate textures structure\n", 2);
		exit(1);
	}
	g->textures->north = malloc(sizeof(t_texture));
	g->textures->south = malloc(sizeof(t_texture));
	g->textures->east = malloc(sizeof(t_texture));
	g->textures->west = malloc(sizeof(t_texture));
	g->textures->sky = malloc(sizeof(t_texture));
	g->textures->portal_gun = malloc(sizeof(t_texture));
	if (!g->textures->north || !g->textures->south || !g->textures->east
		|| !g->textures->west || !g->textures->sky || !g->textures->portal_gun)
	{
		ft_putstr_fd("Error\nFailed to allocate texture structures\n", 2);
		destroy_textures(g);
		exit(1);
	}
}

/**
 * Loads the wall textures from the map errors structure.
 * Uses the mlx_xpm_file_to_image function to load the textures.
 */
void	load_textures(t_game *g, t_map *parsed)
{
	init_textures(g);
	g->textures->portal_gun->img = mlx_xpm_file_to_image(g->mlx,
			"./resources/textures/portal_gun.xpm",
			&g->textures->portal_gun->width,
			&g->textures->portal_gun->height);
	if (g->textures->portal_gun->img)
		g->textures->portal_gun->data
			= mlx_get_data_addr(g->textures->portal_gun->img,
				&g->textures->portal_gun->bpp,
				&g->textures->portal_gun->size_line,
				&g->textures->portal_gun->endian);
	g->textures->sky->img = mlx_xpm_file_to_image(g->mlx,
			"./resources/textures/planet_sky.xpm", &g->textures->sky->width,
			&g->textures->sky->height);
	if (g->textures->sky->img)
		g->textures->sky->data = mlx_get_data_addr(g->textures->sky->img,
				&g->textures->sky->bpp, &g->textures->sky->size_line,
				&g->textures->sky->endian);
	load_wall_textures(g, parsed);
	g->sky_offset_x = 0;
}

/**
 * Destroys the texture images in the game.
 */
static void	destroy_texture_images(t_game *g)
{
	if (g->textures->north && g->textures->north->img)
		mlx_destroy_image(g->mlx, g->textures->north->img);
	if (g->textures->south && g->textures->south->img)
		mlx_destroy_image(g->mlx, g->textures->south->img);
	if (g->textures->east && g->textures->east->img)
		mlx_destroy_image(g->mlx, g->textures->east->img);
	if (g->textures->west && g->textures->west->img)
		mlx_destroy_image(g->mlx, g->textures->west->img);
	if (g->textures->sky && g->textures->sky->img)
		mlx_destroy_image(g->mlx, g->textures->sky->img);
	if (g->textures->portal_gun && g->textures->portal_gun->img)
		mlx_destroy_image(g->mlx, g->textures->portal_gun->img);
}

/**
 * Frees the texture structures in the game.
 * This function frees each texture and then the textures structure
 * itself.
 */
static void	free_texture_structures(t_game *g)
{
	if (g->textures->north)
		free(g->textures->north);
	if (g->textures->south)
		free(g->textures->south);
	if (g->textures->east)
		free(g->textures->east);
	if (g->textures->west)
		free(g->textures->west);
	if (g->textures->sky)
		free(g->textures->sky);
	if (g->textures->portal_gun)
		free(g->textures->portal_gun);
}

/**
 * Destroys all textures in the game.
 * This function is called when the game is closed or when textures
 * need to be reloaded.
 */
void	destroy_textures(t_game *g)
{
	if (!g->textures)
		return ;
	destroy_texture_images(g);
	free_texture_structures(g);
	free(g->textures);
	g->textures = NULL;
}
