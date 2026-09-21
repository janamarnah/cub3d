/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwhusse <siwhusse@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 23:05:00 by siwhusse          #+#    #+#             */
/*   Updated: 2026/09/15 23:20:20 by siwhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_graphics(t_game *g)
{
	g->mlx = mlx_init();
	if (!g->mlx)
		error_exit(g, "mlx initialization failed");
	g->win = mlx_new_window(g->mlx, WIDTH, HEIGHT, "cub3D");
	if (!g->win)
		error_exit(g, "window creation failed");
	g->frame.ptr = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	if (!g->frame.ptr)
		error_exit(g, "image creation failed");
	g->frame.addr = mlx_get_data_addr(g->frame.ptr, &g->frame.bpp,
			&g->frame.line, &g->frame.endian);
	g->frame.w = WIDTH;
	g->frame.h = HEIGHT;
}

void	load_textures(t_game *g)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		g->tex.img[i].ptr = mlx_xpm_file_to_image(g->mlx,
				g->tex.path[i], &g->tex.img[i].w, &g->tex.img[i].h);
		if (!g->tex.img[i].ptr)
			error_exit(g, "cannot load XPM texture");
		g->tex.img[i].addr = mlx_get_data_addr(g->tex.img[i].ptr,
				&g->tex.img[i].bpp, &g->tex.img[i].line,
				&g->tex.img[i].endian);
	}
}
