/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwhusse <siwhusse@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 10:05:00 by siwhusse          #+#    #+#             */
/*   Updated: 2026/09/16 10:40:00 by siwhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	map_cell(t_game *g, int y, int x)
{
	if (y < 0 || y >= g->rows || x < 0)
		return (' ');
	if (x >= str_len(g->map[y]))
		return (' ');
	return (g->map[y][x]);
}

static int	tile_color(char c)
{
	if (c == '1')
		return (MINI_WALL);
	if (c == '0')
		return (MINI_FLOOR);
	return (MINI_VOID);
}

static void	draw_frame(t_game *g)
{
	int	x;
	int	y;
	int	w;
	int	h;

	w = mini_cells(g->cols, g->mini_tile) * g->mini_tile;
	h = mini_cells(g->rows, g->mini_tile) * g->mini_tile;
	y = -3;
	while (++y < h + 2)
	{
		x = -3;
		while (++x < w + 2)
			mini_put(g, MINI_PAD + x, MINI_PAD + y, MINI_BORDER);
	}
}

static void	draw_minimap_tiles(t_game *g)
{
	int	x;
	int	y;
	int	t;

	t = g->mini_tile;
	y = -1;
	while (++y < mini_cells(g->rows, t))
	{
		x = -1;
		while (++x < mini_cells(g->cols, t))
			draw_block(g, MINI_PAD + x * t, MINI_PAD + y * t,
				tile_color(map_cell(g, y, x)));
	}
}

void	draw_minimap(t_game *g)
{
	draw_frame(g);
	draw_minimap_tiles(g);
	draw_player(g);
}
