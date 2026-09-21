/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwhusse <siwhusse@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 10:06:00 by siwhusse          #+#    #+#             */
/*   Updated: 2026/09/16 10:41:00 by siwhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_minimap(t_game *g)
{
	int	tile;

	tile = MINI_SIZE / g->cols;
	if (MINI_SIZE / g->rows < tile)
		tile = MINI_SIZE / g->rows;
	if (tile > MINI_TILE_MAX)
		tile = MINI_TILE_MAX;
	if (tile < MINI_TILE_MIN)
		tile = MINI_TILE_MIN;
	g->mini_tile = tile;
}

int	mini_cells(int count, int tile)
{
	if (count * tile > MINI_SIZE)
		return (MINI_SIZE / tile);
	return (count);
}

void	mini_put(t_game *g, int x, int y, int color)
{
	if (x < MINI_PAD - 2 || y < MINI_PAD - 2)
		return ;
	if (x > MINI_PAD + MINI_SIZE + 1 || y > MINI_PAD + MINI_SIZE + 1)
		return ;
	pixel_put(&g->frame, x, y, color);
}

void	draw_block(t_game *g, int x, int y, int color)
{
	int	i;
	int	j;

	j = -1;
	while (++j < g->mini_tile)
	{
		i = -1;
		while (++i < g->mini_tile)
			mini_put(g, x + i, y + j, color);
	}
}

void	draw_player(t_game *g)
{
	int	px;
	int	py;
	int	x;
	int	y;

	px = MINI_PAD + (int)(g->p.x * g->mini_tile);
	py = MINI_PAD + (int)(g->p.y * g->mini_tile);
	y = -3;
	while (++y < 3)
	{
		x = -3;
		while (++x < 3)
		{
			if (x * x + y * y <= 4)
				mini_put(g, px + x, py + y, MINI_PLAYER);
		}
	}
	x = 0;
	while (++x <= g->mini_tile)
		mini_put(g, px + (int)(g->p.dx * x),
			py + (int)(g->p.dy * x), MINI_PLAYER);
}
