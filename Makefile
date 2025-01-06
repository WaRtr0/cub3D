NAME = cub3d
CC = cc

OPTI = 1

RM = rm -rf

INCLUDES_DIR = includes

INCLUDES = $(INCLUDES_DIR)/game.h\
		   $(INCLUDES_DIR)/layer.h\
		   $(INCLUDES_DIR)/types.h\
		   $(INCLUDES_DIR)/hook.h\
		   $(INCLUDES_DIR)/draw.h\
		   $(INCLUDES_DIR)/font.h\
		   $(INCLUDES_DIR)/cub.h\
		   $(INCLUDES_DIR)/raycast.h\
		   $(INCLUDES_DIR)/utils.h\
		   $(INCLUDES_DIR)/view.h\
		   $(INCLUDES_DIR)/parsing.h\
		   $(INCLUDES_DIR)/player.h\


FLAG_OPTI =  -O3 -march=native -flto -ffast-math
DEFAULT_FLAG = -g3
CFLAGS = -Wall -Wextra -Werror

ifeq ($(OPTI), 1)
	CFLAGS += $(FLAG_OPTI)
else
	CFLAGS += $(DEFAULT_FLAG)
endif

MLXFLAGS = -lX11 -lXext -lm -g3

SRC_DIR = srcs
BUILD_DIR = .obj

SRC_FILE = main.c\
           game/game_new.c game/game_init.c game/game_run.c game/game_destroy.c game/game_time.c game/game_handle.c  game/game_set.c\
		   layer/layer_clear.c layer/layer_create.c layer/layer_destroy.c layer/layer_dupe.c layer/layer_fill.c layer/layer_get_offset.c layer/layer_get_pixel.c layer/layer_set_offset.c layer/layer_set_pixel.c layer/layer_rotate.c layer/layer_volatile.c layer/layer_split_fill.c layer/layer_add_texture.c\
		   layer/stack/layer_stack_add.c layer/stack/layer_stack_create.c layer/stack/layer_stack_destroy.c layer/stack/layer_stack_get.c layer/stack/layer_stack_render.c\
		   layer/group/layer_group_create.c layer/group/layer_group_destroy.c layer/group/layer_group_add.c layer/group/layer_group_get.c\
		   draw/draw_circle_fill.c draw/draw_circle.c draw/draw_line.c draw/draw_rect_fill.c draw/draw_rect.c draw/draw_triangle_fill.c draw/draw_triangle.c draw/draw_xpm_texture.c draw/draw_text.c\
		   utils/int_to_pixel.c utils/pixel_create.c utils/pixel_to_int.c utils/prerr.c utils/math_utils_bonus.c utils/vector2.c\
		   raycast/raycast.c raycast/ray_dda.c\
		   view/view_create.c\
		   font.c\
		   player/player_move.c player/door_manager.c\
		   parsing/parsing.c parsing/parsing_map.c parsing/parsing_checks.c\

SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILE))

OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))

LIBFT = libft
LIBMLX = minilibx-linux
LIBFTNAME = libft.a
LIBMLXNAME = libmlx_Linux.a
LIBFTA = $(LIBFT)/$(LIBFTNAME)
LIBMLXA = $(LIBMLX)/$(LIBMLXNAME)

LFLAGS = -L$(LIBFT) -L$(LIBMLX) -lft -lmlx_Linux $(MLXFLAGS) -I $(LIBFT) -I $(LIBMLX)

$(NAME): $(LIBFTA) $(LIBMLXA) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LFLAGS) -I $(INCLUDES_DIR)

all :    $(NAME)

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.c $(INCLUDES) Makefile
	echo "Creating directory $(@D)"
	mkdir -p $(@D)
	echo "Compiling $< to $@"
	$(CC) $(CFLAGS) -o $@ -c $< -I $(INCLUDES_DIR)

$(LIBFTA) :  force
	$(MAKE) -C $(LIBFT)
	
$(LIBMLXA) : force
	$(MAKE) -C $(LIBMLX)
	
clean:
	$(MAKE) clean -C $(LIBFT) 
	$(MAKE) clean -C $(LIBMLX) 
	$(RM) $(BUILD_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFT)
	$(RM) $(NAME) $(LIBMLXA)

re: fclean all
	
force:

.PHONY: all clean fclean re