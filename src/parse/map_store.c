/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_store.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwhusse <siwhusse@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 22:47:00 by siwhusse          #+#    #+#             */
/*   Updated: 2026/09/15 23:19:20 by siwhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	last_map_line(char **lines, int at)
{
	int	n;

	n = 0;
	while (lines[at + n])
		n++;
	while (n > 0 && lines[at + n - 1][0] == '\0')
		n--;
	return (n);
}

static int	widest_line(char **map)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (map[i])
	{
		if (str_len(map[i]) > len)
			len = str_len(map[i]);
		i++;
	}
	return (len);
}

static void	copy_map(t_game *g, char **lines, int at, int n)
{
	int	i;

	g->map = malloc(sizeof(char *) * (n + 1));
	if (!g->map)
		error_exit(g, "allocation failure");
	i = 0;
	while (i < n)
	{
		if (lines[at + i][0] == '\0')
			error_exit(g, "empty line inside map");
		g->map[i] = x_strdup(lines[at + i]);
		if (!g->map[i])
			error_exit(g, "allocation failure");
		i++;
	}
	g->map[i] = NULL;
	g->rows = n;
	g->cols = widest_line(g->map);
}

void	set_map(t_game *g, char **lines, int at)
{
	int	n;

	n = last_map_line(lines, at);
	if (n == 0)
		error_exit(g, "empty map");
	copy_map(g, lines, at, n);
}
