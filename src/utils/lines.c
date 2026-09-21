/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwhusse <siwhusse@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 22:31:00 by siwhusse          #+#    #+#             */
/*   Updated: 2026/09/15 23:18:20 by siwhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	line_count(char *s)
{
	int	i;
	int	n;

	i = 0;
	n = 1;
	while (s[i])
		if (s[i++] == '\n')
			n++;
	return (n);
}

static char	*make_line(char *s, int start, int end)
{
	if (end > start && s[end - 1] == '\r')
		end--;
	return (x_substr(s, start, end - start));
}

char	**split_lines(char *s)
{
	char	**v;
	int		i;
	int		j;
	int		k;

	v = malloc(sizeof(char *) * (line_count(s) + 1));
	if (!v)
		return (NULL);
	i = 0;
	k = 0;
	while (s[i])
	{
		j = i;
		while (s[j] && s[j] != '\n')
			j++;
		v[k++] = make_line(s, i, j);
		i = j + (s[j] == '\n');
	}
	v[k] = NULL;
	return (v);
}

void	free_split(char **v)
{
	int	i;

	i = 0;
	if (!v)
		return ;
	while (v[i])
		free(v[i++]);
	free(v);
}
