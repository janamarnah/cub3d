/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwhusse <siwhusse@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 23:21:00 by siwhusse          #+#    #+#             */
/*   Updated: 2026/09/15 23:25:00 by siwhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	rotate(t_game *g, double angle)
{
	double	old;

	old = g->p.dx;
	g->p.dx = g->p.dx * cos(angle) - g->p.dy * sin(angle);
	g->p.dy = old * sin(angle) + g->p.dy * cos(angle);
	old = g->p.px;
	g->p.px = g->p.px * cos(angle) - g->p.py * sin(angle);
	g->p.py = old * sin(angle) + g->p.py * cos(angle);
}

static int	blocked(t_game *g, double x, double y)
{
	double	r;

	r = 0.22;
	if (g->map[(int)(y - r)][(int)(x - r)] == '1')
		return (1);
	if (g->map[(int)(y - r)][(int)(x + r)] == '1')
		return (1);
	if (g->map[(int)(y + r)][(int)(x - r)] == '1')
		return (1);
	if (g->map[(int)(y + r)][(int)(x + r)] == '1')
		return (1);
	return (0);
}

static void	move(t_game *g, double dx, double dy)
{
	if (!blocked(g, g->p.x + dx, g->p.y))
		g->p.x += dx;
	if (!blocked(g, g->p.x, g->p.y + dy))
		g->p.y += dy;
}

static void	walk(t_game *g)
{
	double	dx;
	double	dy;
	double	len;

	dx = g->p.dx * (g->key_w - g->key_s);
	dy = g->p.dy * (g->key_w - g->key_s);
	dx += g->p.px * (g->key_d - g->key_a);
	dy += g->p.py * (g->key_d - g->key_a);
	len = sqrt(dx * dx + dy * dy);
	if (len > 0.0)
		move(g, dx / len * MOVE, dy / len * MOVE);
}

void	update_player(t_game *g)
{
	walk(g);
	if (g->key_left && !g->key_right)
		rotate(g, -ROT);
	if (g->key_right && !g->key_left)
		rotate(g, ROT);
}
