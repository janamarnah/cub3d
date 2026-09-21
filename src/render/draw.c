/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwhusse <siwhusse@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 22:56:00 by siwhusse          #+#    #+#             */
/*   Updated: 2026/09/15 23:19:50 by siwhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	wall_hit(t_game *g, t_ray *r)
{
	double	hit;

	if (r->side == 0)
		hit = g->p.y + r->dist * r->dy;
	else
		hit = g->p.x + r->dist * r->dx;
	return (hit - floor(hit));
}

static int	texture_x(t_game *g, t_ray *r, t_img *t)
{
	int	x;

	x = (int)(wall_hit(g, r) * t->w);
	if (r->side == 0 && r->dx > 0)
		x = t->w - x - 1;
	if (r->side == 1 && r->dy < 0)
		x = t->w - x - 1;
	return (x);
}

static void	wall_bounds(t_ray *r, int *start, int *end)
{
	int	height;

	height = (int)(HEIGHT / r->dist);
	*start = -height / 2 + HEIGHT / 2;
	*end = height / 2 + HEIGHT / 2;
	if (*start < 0)
		*start = 0;
	if (*end >= HEIGHT)
		*end = HEIGHT - 1;
}

void	draw_column(t_game *g, t_ray *r, int x, int id)
{
	t_img	*t;
	double	step;
	double	pos;
	int		y;
	int		end;

	t = &g->tex.img[id];
	wall_bounds(r, &y, &end);
	step = t->h * r->dist / HEIGHT;
	pos = (y - HEIGHT / 2 + HEIGHT / (2.0 * r->dist)) * step;
	while (y <= end)
	{
		pixel_put(&g->frame, x, y, pixel_get(t,
				texture_x(g, r, t), (int)pos & (t->h - 1)));
		pos += step;
		y++;
	}
}

void	render(t_game *g)
{
	int	x;

	draw_background(g);
	x = 0;
	while (x < WIDTH)
	{
		cast_ray(g, x);
		x++;
	}
	draw_minimap(g);
	mlx_put_image_to_window(g->mlx, g->win, g->frame.ptr, 0, 0);
}
