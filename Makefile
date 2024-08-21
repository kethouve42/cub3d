NAME = cub3d_THE_GAME

SRCS_DIR = srcs
INCLUDE = ./
MLX_PATH = minilibx-linux/
MLX_LIB = libmlx_Linux.a

OBJDIR = obj
CC = gcc
CFLAGS = -lm -g
MLXFLAGS = -Werror -Wall -Wextra -lX11 -lXext -lm

FILES = check_map.c\
		check_map_bis.c\
		close.c\
		close_bis.c\
		cub3d.c\
		enemies.c\
		enemies_bis.c\
		enemies_ter.c\
		get_next_line.c\
		graphic_info.c\
		graphic_info_bis.c\
		graphic_info_ter.c\
		init.c\
		init_bis.c\
		minimap.c\
		pathfinding.c\
		player.c\
		player_bis.c\
		player_movement.c\
		raycast.c\
		raycast_bis.c\
		raycast_ter.c\
		shoot.c\
		shoot_bis.c\
		sound.c\
		sprite.c\
		sprite_bis.c\
		sprite_ter.c\
		time_system.c\
		utils1.c\
		utils2.c\
		utils3.c\
		debug.c

SRC = $(addprefix $(SRCS_DIR)/, $(FILES))
OBJ = $(addprefix $(OBJDIR)/, $(FILES:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_PATH)$(MLX_LIB) $(MLXFLAGS) -o $@ -I$(MLX_PATH) -I$(INCLUDE)

$(OBJDIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
