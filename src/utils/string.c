/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwhusse <siwhusse@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 22:33:00 by siwhusse          #+#    #+#             */
/*   Updated: 2026/09/15 23:18:30 by siwhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	str_len(char *s)
{
	int	n;

	n = 0;
	while (s && s[n])
		n++;
	return (n);
}

char	*x_strdup(char *s)
{
	char	*r;
	int		i;

	r = malloc(str_len(s) + 1);
	if (!r)
		return (NULL);
	i = -1;
	while (s[++i])
		r[i] = s[i];
	r[i] = 0;
	return (r);
}

char	*x_substr(char *s, int start, int len)
{
	char	*r;
	int		i;

	r = malloc(len + 1);
	if (!r)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		r[i] = s[start + i];
		i++;
	}
	r[i] = 0;
	return (r);
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\r'
		|| c == '\v' || c == '\f');
}
