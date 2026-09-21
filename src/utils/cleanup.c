/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwhusse <siwhusse@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 22:35:00 by siwhusse          #+#    #+#             */
/*   Updated: 2026/09/15 23:18:40 by siwhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	destroy_images(t_game *g)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (g->mlx && g->tex.img[i].ptr)
			mlx_destroy_image(g->mlx, g->tex.img[i].ptr);
		i++;
	}
	if (g->mlx && g->frame.ptr)
		mlx_destroy_image(g->mlx, g->frame.ptr);
}

void	cleanup(t_game *g)
{
	int	i;

	destroy_images(g);
	if (g->mlx && g->win)
		mlx_destroy_window(g->mlx, g->win);
	i = 0;
	while (i < 4)
		free(g->tex.path[i++]);
	free_split(g->map);
}

void	error_exit(t_game *g, char *msg)
{
	write(2, "Error\n", 6);
	if (msg)
	{
		write(2, msg, str_len(msg));
		write(2, "\n", 1);
	}
	cleanup(g);
	exit(1);
}

int	close_game(t_game *g)
{
	cleanup(g);
	exit(0);
	return (0);
}
