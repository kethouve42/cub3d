NAME = cub3d_THE_GAME

SRCS = ./
INCLUDE = ./
MLX_PATH = minilibx-linux/
MLX_LIB = libmlx_Linux.a

CC = gcc
CFLAGS = -lm -g
MLXFLAGS = -Werror -Wall -Wextra -lX11 -lXext -lm

FILES = cub3d.c\
		raycast.c\
		parse.c\
		get_next_line.c\
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