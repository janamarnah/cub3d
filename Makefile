NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror
INC = -Iinclude -Iminilibx-linux
MLX = minilibx-linux/libmlx.a
LIBS = -Lminilibx-linux -lmlx -lXext -lX11 -lm -lz
SRC = src/main.c src/utils/string.c src/utils/lines.c src/utils/cleanup.c \
	src/parse/read.c src/parse/elements.c src/parse/map_store.c src/parse/color.c src/parse/map.c \
	src/parse/player.c src/render/init.c src/render/pixel.c src/render/ray.c \
	src/render/draw.c src/render/background.c \
	src/render/minimap.c src/render/minimap_utils.c src/events/keys.c \
	src/events/movement.c src/events/loop.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(MLX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

$(MLX):
	$(MAKE) -C minilibx-linux

%.o: %.c include/cub3d.h
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJ)
	@if [ -d minilibx-linux ]; then $(MAKE) -C minilibx-linux clean; fi

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
