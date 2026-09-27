/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwhusse <siwhusse@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 22:20:00 by siwhusse          #+#    #+#             */
/*   Updated: 2026/09/15 23:18:00 by siwhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	has_cub(char *s)
{
	int	n;

	n = str_len(s);
	if (n < 5)
		return (0);
	return (s[n - 4] == '.' && s[n - 3] == 'c'
		&& s[n - 2] == 'u' && s[n - 1] == 'b');
}

int	main(int ac, char **av)
{
	t_game	g;

	if (ac != 2 || !has_cub(av[1]))
	{
		write(2, "Error\nusage: ./cub3D scene.cub\n", 32);
		return (1);
	}
	g = (t_game){0};
	g.floor = -1;
	g.ceiling = -1;
	parse_scene(&g, av[1]);
	init_graphics(&g);
	load_textures(&g);
	init_minimap(&g);
	render(&g);
	mlx_hook(g.win, 2, 1L << 0, key_press, &g);
	mlx_hook(g.win, 3, 1L << 1, key_release, &g);
	mlx_hook(g.win, 17, 0, close_game, &g);
	mlx_loop_hook(g.mlx, loop, &g);
	mlx_loop(g.mlx);
	return (0);
}
