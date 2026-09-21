/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwhusse <siwhusse@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 22:44:00 by siwhusse          #+#    #+#             */
/*   Updated: 2026/09/15 23:19:10 by siwhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	cell(t_game *g, int y, int x)
{
	if (y < 0 || y >= g->rows || x < 0)
		return (' ');
	if (x >= str_len(g->map[y]))
		return (' ');
	return (g->map[y][x]);
}

static int	walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W');
}

static void	check_cell(t_game *g, int y, int x, int *players)
{
	char	c;

	c = cell(g, y, x);
	if (c != ' ' && c != '0' && c != '1' && c != 'N'
		&& c != 'S' && c != 'E' && c != 'W')
		error_exit(g, "invalid map character");
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		(*players)++;
	if (walkable(c) && (cell(g, y - 1, x) == ' '
			|| cell(g, y + 1, x) == ' ' || cell(g, y, x - 1) == ' '
			|| cell(g, y, x + 1) == ' '))
		error_exit(g, "map is not closed");
}

void	validate_map(t_game *g)
{
	int	y;
	int	x;
	int	players;

	if (!g->tex.path[0] || !g->tex.path[1] || !g->tex.path[2]
		|| !g->tex.path[3] || g->floor < 0 || g->ceiling < 0)
		error_exit(g, "missing scene element");
	players = 0;
	y = -1;
	while (++y < g->rows)
	{
		x = -1;
		while (++x < str_len(g->map[y]))
			check_cell(g, y, x, &players);
	}
	if (players != 1)
		error_exit(g, "map must contain exactly one player");
}
