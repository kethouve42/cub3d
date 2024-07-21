NAME = cub3d_THE_GAME

SRCS = ./
INCLUDE = ./
MLX_PATH = minilibx-linux/
MLX_LIB = libmlx_Linux.a

CC = gcc
CFLAGS = -lm -g
MLXFLAGS = -Werror -Wall -Wextra -lX11 -lXext -lm

FILES = check_map.c\
		check_map_bis.c\
		cub3d.c\
		get_next_line.c\
		graphic_info.c\
		graphic_info_bis.c\
		pathfinding.c\
		player.c\
		raycast.c\
		utils1.c\
		utils2.c\
		utils3.c

OBJ = $(addprefix $(SRCS), $(FILES:.c=.o))

all: $(NAME) clean

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_PATH)$(MLX_LIB) $(MLXFLAGS) -o $@ -I$(MLX_PATH) -I$(INCLUDE)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all