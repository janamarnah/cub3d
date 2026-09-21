/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwhusse <siwhusse@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 22:15:00 by siwhusse          #+#    #+#             */
/*   Updated: 2026/09/16 01:59:14 by siwhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# define WIDTH 1000
# define HEIGHT 700
# define MOVE 0.035
# define ROT 0.020

# define MINI_SIZE 140
# define MINI_PAD 10
# define MINI_TILE_MIN 1
# define MINI_TILE_MAX 12
# define MINI_WALL 0x4C566A
# define MINI_FLOOR 0xD8DEE9
# define MINI_VOID 0x101318
# define MINI_BORDER 0xECEFF4
# define MINI_PLAYER 0xFF0000

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line;
	int		endian;
	int		w;
	int		h;
}	t_img;

typedef struct s_tex
{
	char	*path[4];
	t_img	img[4];
}	t_tex;

typedef struct s_player
{
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	px;
	double	py;
}	t_player;

typedef struct s_ray
{
	double	cam;
	double	dx;
	double	dy;
	double	sx;
	double	sy;
	double	ddx;
	double	ddy;
	double	dist;
	int		mx;
	int		my;
	int		stepx;
	int		stepy;
	int		side;
}	t_ray;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		frame;
	t_tex		tex;
	t_player	p;
	char		**map;
	int			rows;
	int			cols;
	int			mini_tile;
	int			floor;
	int			ceiling;
	int			key_w;
	int			key_s;
	int			key_a;
	int			key_d;
	int			key_left;
	int			key_right;
}	t_game;

void	error_exit(t_game *g, char *msg);
void	cleanup(t_game *g);
int		close_game(t_game *g);
char	*x_strdup(char *s);
char	*x_substr(char *s, int start, int len);
int		str_len(char *s);
int		is_space(char c);
void	free_split(char **v);
char	**split_lines(char *s);
void	parse_scene(t_game *g, char *file);
void	parse_elements(t_game *g, char **lines);
void	set_map(t_game *g, char **lines, int at);
int		parse_color(t_game *g, char *s);
void	validate_map(t_game *g);
void	init_player(t_game *g);
void	init_graphics(t_game *g);
void	load_textures(t_game *g);
void	render(t_game *g);
void	draw_background(t_game *g);
void	cast_ray(t_game *g, int x);
void	draw_column(t_game *g, t_ray *r, int x, int id);
int		key_press(int key, t_game *g);
int		key_release(int key, t_game *g);
int		loop(t_game *g);
void	update_player(t_game *g);
int		pixel_get(t_img *img, int x, int y);
void	pixel_put(t_img *img, int x, int y, int color);
void	init_minimap(t_game *g);
void	draw_minimap(t_game *g);
int		mini_cells(int count, int tile);
void	mini_put(t_game *g, int x, int y, int color);
void	draw_block(t_game *g, int x, int y, int color);
void	draw_player(t_game *g);

#endif
