NAME = cub3d

NAME_BONUS = cub3d_THE_GAME

SRCS_DIR = srcs
SRCS_BNS_DIR = srcs_bonus

INCLUDE = ./
MLX_PATH = minilibx-linux/
MLX_LIB = libmlx_Linux.a

OBJDIR = obj
OBJDIR_BNS = obj
CC = gcc
CFLAGS = -lm -g
MLXFLAGS = -Werror -Wall -Wextra -lX11 -lXext -lm

FILES = check_map.c\
		check_map_bis.c\
		close.c\
		cub3d.c\
		get_next_line.c\
		graphic_info.c\
		graphic_info_bis.c\
		pathfinding.c\
		player.c\
		raycast.c\
		raycast_bis.c\
		utils1.c\
		utils2.c\
		utils3.c\
		debug.c

FILES_BNS = check_map_bonus.c\
		check_map_bis_bonus.c\
		close_bonus.c\
		close_bis_bonus.c\
		cub3d_bonus.c\
		enemies_bonus.c\
		enemies_bis_bonus.c\
		enemies_ter_bonus.c\
		get_next_line_bonus.c\
		graphic_info_bonus.c\
		graphic_info_bis_bonus.c\
		graphic_info_ter_bonus.c\
		init_bonus.c\
		init_bis_bonus.c\
		init_ter_bonus.c\
		minimap_bonus.c\
		pathfinding_bonus.c\
		player_bonus.c\
		player_bis_bonus.c\
		player_movement_bonus.c\
		raycast_bonus.c\
		raycast_bis_bonus.c\
		raycast_ter_bonus.c\
		shoot_bonus.c\
		shoot_bis_bonus.c\
		sound_bonus.c\
		sprite_bonus.c\
		sprite_bis_bonus.c\
		sprite_ter_bonus.c\
		time_system_bonus.c\
		utils1_bonus.c\
		utils2_bonus.c\
		utils3_bonus.c\
		debug_bonus.c

SRC = $(addprefix $(SRCS_DIR)/, $(FILES))
OBJ = $(addprefix $(OBJDIR)/, $(FILES:.c=.o))
OBJ_BNS = $(addprefix $(OBJDIR_BNS)/, $(FILES_BNS:.c=.o))

all: $(NAME)

bonus : $(NAME_BONUS)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_PATH)$(MLX_LIB) $(MLXFLAGS) -o $@ -I$(MLX_PATH) -I$(INCLUDE)

$(NAME_BONUS): $(OBJ_BNS)
	$(CC) $(CFLAGS) $(OBJ_BNS) $(MLX_PATH)$(MLX_LIB) $(MLXFLAGS) -o $@ -I$(MLX_PATH) -I$(INCLUDE)

$(OBJDIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR_BNS)/%.o: $(SRCS_BNS_DIR)/%.c
	mkdir -p $(OBJDIR_BNS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -f $(OBJ_BNS)
	rm -rf $(OBJDIR)
	rm -rf $(OBJDIR_BNS)

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)

re: fclean all
