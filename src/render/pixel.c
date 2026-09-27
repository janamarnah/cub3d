/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwhusse <siwhusse@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 23:02:00 by siwhusse          #+#    #+#             */
/*   Updated: 2026/09/15 23:20:10 by siwhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->w || y >= img->h)
		return ;
	dst = img->addr + y * img->line + x * (img->bpp / 8);
	*(unsigned int *)dst = color;
}

int	pixel_get(t_img *img, int x, int y)
{
	char	*src;

	if (x < 0 || y < 0 || x >= img->w || y >= img->h)
		return (0);
	src = img->addr + y * img->line + x * (img->bpp / 8);
	return (*(unsigned int *)src);
}
