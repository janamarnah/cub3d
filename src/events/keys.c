/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwhusse <siwhusse@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 22:29:03 by siwhusse          #+#    #+#             */
/*   Updated: 2026/09/15 23:18:10 by siwhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_move_key(int key, t_game *g, int state)
{
	if (key == 119)
		g->key_w = state;
	else if (key == 115)
		g->key_s = state;
	else if (key == 97)
		g->key_a = state;
	else if (key == 100)
		g->key_d = state;
	else if (key == 65361)
		g->key_left = state;
	else if (key == 65363)
		g->key_right = state;
}

int	key_press(int key, t_game *g)
{
	if (key == 65307)
		return (close_game(g));
	set_move_key(key, g, 1);
	return (0);
}

int	key_release(int key, t_game *g)
{
	set_move_key(key, g, 0);
	return (0);
}
