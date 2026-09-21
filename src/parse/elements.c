/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwhusse <siwhusse@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 22:38:00 by siwhusse          #+#    #+#             */
/*   Updated: 2026/09/15 23:18:50 by siwhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*value(char *s, int n)
{
	int	start;
	int	end;

	start = n;
	while (is_space(s[start]))
		start++;
	end = str_len(s);
	while (end > start && is_space(s[end - 1]))
		end--;
	if (start == end)
		return (NULL);
	return (x_substr(s, start, end - start));
}

static int	texture_id(char *s)
{
	if (s[0] == 'N' && s[1] == 'O' && is_space(s[2]))
		return (0);
	if (s[0] == 'S' && s[1] == 'O' && is_space(s[2]))
		return (1);
	if (s[0] == 'W' && s[1] == 'E' && is_space(s[2]))
		return (2);
	if (s[0] == 'E' && s[1] == 'A' && is_space(s[2]))
		return (3);
	return (-1);
}

static int	texture(t_game *g, char *s)
{
	int	id;

	id = texture_id(s);
	if (id < 0)
		return (0);
	if (g->tex.path[id])
		error_exit(g, "duplicate texture");
	g->tex.path[id] = value(s, 2);
	if (!g->tex.path[id])
		error_exit(g, "missing texture path");
	return (1);
}

static int	map_line(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '0' && s[i] != '1'
			&& s[i] != 'N' && s[i] != 'S'
			&& s[i] != 'E' && s[i] != 'W')
			return (0);
		i++;
	}
	return (i > 0);
}

void	parse_elements(t_game *g, char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		if (!lines[i][0])
			i++;
		else if (map_line(lines[i]))
			return (set_map(g, lines, i));
		else if (texture(g, lines[i]) || parse_color(g, lines[i]))
			i++;
		else
			error_exit(g, "invalid scene element");
	}
	error_exit(g, "missing map");
}
