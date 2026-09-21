/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwhusse <siwhusse@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 22:41:00 by siwhusse          #+#    #+#             */
/*   Updated: 2026/09/15 23:19:00 by siwhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	skip_space(char *s, int *i)
{
	while (is_space(s[*i]))
		(*i)++;
}

static int	number(char *s, int *i, int *ok)
{
	int	n;
	int	digits;

	skip_space(s, i);
	n = 0;
	digits = 0;
	while (s[*i] >= '0' && s[*i] <= '9')
	{
		n = n * 10 + s[(*i)++] - '0';
		digits++;
	}
	if (!digits || n > 255)
		*ok = 0;
	skip_space(s, i);
	return (n);
}

static int	rgb(char *s, int i, int *ok)
{
	int	a;
	int	b;
	int	c;

	a = number(s, &i, ok);
	if (s[i] != ',')
		*ok = 0;
	else
		i++;
	b = number(s, &i, ok);
	if (s[i] != ',')
		*ok = 0;
	else
		i++;
	c = number(s, &i, ok);
	skip_space(s, &i);
	if (s[i])
		*ok = 0;
	return ((a << 16) | (b << 8) | c);
}

int	parse_color(t_game *g, char *s)
{
	int	ok;
	int	c;

	if ((s[0] != 'F' && s[0] != 'C') || !is_space(s[1]))
		return (0);
	ok = 1;
	c = rgb(s, 1, &ok);
	if (!ok)
		error_exit(g, "invalid RGB color");
	if (s[0] == 'F' && g->floor != -1)
		error_exit(g, "duplicate floor color");
	if (s[0] == 'C' && g->ceiling != -1)
		error_exit(g, "duplicate ceiling color");
	if (s[0] == 'F')
		g->floor = c;
	else
		g->ceiling = c;
	return (1);
}
