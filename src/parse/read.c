/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwhusse <siwhusse@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 22:50:00 by siwhusse          #+#    #+#             */
/*   Updated: 2026/09/15 23:19:30 by siwhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*grow(char *old, char *buf, int used, int add)
{
	char	*n;
	int		i;

	n = malloc(used + add + 1);
	if (!n)
		return (free(old), NULL);
	i = -1;
	while (++i < used)
		n[i] = old[i];
	i = -1;
	while (++i < add)
		n[used + i] = buf[i];
	n[used + add] = 0;
	free(old);
	return (n);
}

static char	*read_content(int fd)
{
	char	buf[4096];
	char	*out;
	int		n;
	int		used;

	out = NULL;
	used = 0;
	n = read(fd, buf, sizeof(buf));
	while (n > 0)
	{
		out = grow(out, buf, used, n);
		if (!out)
			return (NULL);
		used += n;
		n = read(fd, buf, sizeof(buf));
	}
	if (n < 0)
		return (free(out), NULL);
	if (!out)
		out = x_strdup("");
	return (out);
}

static char	*read_file(char *path)
{
	char	*out;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	out = read_content(fd);
	close(fd);
	return (out);
}

void	parse_scene(t_game *g, char *file)
{
	char	*raw;
	char	**lines;

	raw = read_file(file);
	if (!raw)
		error_exit(g, "cannot read scene");
	lines = split_lines(raw);
	free(raw);
	if (!lines)
		error_exit(g, "allocation failure");
	parse_elements(g, lines);
	free_split(lines);
	validate_map(g);
	init_player(g);
}
