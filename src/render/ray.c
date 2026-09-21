/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwhusse <siwhusse@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 22:59:00 by siwhusse          #+#    #+#             */
/*   Updated: 2026/09/15 23:20:00 by siwhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_ray(t_game *g, t_ray *r, int x)
{
	double	camera;

	camera = 2.0 * x / (double)WIDTH - 1.0;
	r->dx = g->p.dx + g->p.px * camera;
	r->dy = g->p.dy + g->p.py * camera;
	r->mx = (int)g->p.x;
	r->my = (int)g->p.y;
	r->ddx = 1e30;
	r->ddy = 1e30;
	if (r->dx != 0.0)
		r->ddx = fabs(1.0 / r->dx);
	if (r->dy != 0.0)
		r->ddy = fabs(1.0 / r->dy);
}

static void	init_step(t_game *g, t_ray *r)
{
	r->stepx = 1;
	r->stepy = 1;
	r->sx = (r->mx + 1.0 - g->p.x) * r->ddx;
	r->sy = (r->my + 1.0 - g->p.y) * r->ddy;
	if (r->dx < 0)
	{
		r->stepx = -1;
		r->sx = (g->p.x - r->mx) * r->ddx;
	}
	if (r->dy < 0)
	{
		r->stepy = -1;
		r->sy = (g->p.y - r->my) * r->ddy;
	}
}

static void	dda(t_game *g, t_ray *r)
{
	while (g->map[r->my][r->mx] != '1')
	{
		if (r->sx < r->sy)
		{
			r->sx += r->ddx;
			r->mx += r->stepx;
			r->side = 0;
		}
		else
		{
			r->sy += r->ddy;
			r->my += r->stepy;
			r->side = 1;
		}
	}
	if (r->side == 0)
		r->dist = r->sx - r->ddx;
	else
		r->dist = r->sy - r->ddy;
	if (r->dist < 0.001)
		r->dist = 0.001;
}

static int	texture_id(t_ray *r)
{
	if (r->side == 0 && r->dx > 0)
		return (3);
	if (r->side == 0)
		return (2);
	if (r->dy > 0)
		return (1);
	return (0);
}

void	cast_ray(t_game *g, int x)
{
	t_ray	r;

	init_ray(g, &r, x);
	init_step(g, &r);
	dda(g, &r);
	draw_column(g, &r, x, texture_id(&r));
}
