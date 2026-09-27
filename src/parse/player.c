/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwhusse <siwhusse@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 22:53:00 by siwhusse          #+#    #+#             */
/*   Updated: 2026/09/15 23:19:40 by siwhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	direction(t_player *p, char c)
{
	p->dx = 0;
	p->dy = 0;
	if (c == 'N')
		p->dy = -1;
	if (c == 'S')
		p->dy = 1;
	if (c == 'E')
		p->dx = 1;
	if (c == 'W')
		p->dx = -1;
	p->px = -p->dy * 0.66;
	p->py = p->dx * 0.66;
}

void	init_player(t_game *g)
{
	int		y;
	int		x;
	char	c;

	y = -1;
	while (++y < g->rows)
	{
		x = -1;
		while (g->map[y][++x])
		{
			c = g->map[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				g->p.x = x + 0.5;
				g->p.y = y + 0.5;
				direction(&g->p, c);
				g->map[y][x] = '0';
				return ;
			}
		}
	}
}
