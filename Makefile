NAME = cub3d
NAME_BONUS = cub3d_bonus
CC = cc

OPTI = 1
ASAN = 0

RM = rm -rf

INCLUDES_DIR = includes

INCLUDES = $(INCLUDES_DIR)/game.h\
		   $(INCLUDES_DIR)/layer.h\
		   $(INCLUDES_DIR)/types.h\
		   $(INCLUDES_DIR)/hook.h\
		   $(INCLUDES_DIR)/draw.h\
		   $(INCLUDES_DIR)/cub.h\
		   $(INCLUDES_DIR)/raycast.h\
		   $(INCLUDES_DIR)/utils.h\
		   $(INCLUDES_DIR)/view.h\
		   $(INCLUDES_DIR)/parsing.h\
		   $(INCLUDES_DIR)/player.h\
		   $(INCLUDES_DIR)/map.h\


FLAG_OPTI =  -O3 -march=native -flto -ffast-math
FLAG_ASAN = -fsanitize=address -g3
DEFAULT_FLAG =
CFLAGS = -Wall -Wextra -Werror

ifeq ($(OPTI), 1)
	CFLAGS += $(FLAG_OPTI)
else
	CFLAGS += $(DEFAULT_FLAG)
endif

ifeq ($(ASAN), 1)
	CFLAGS += $(FLAG_ASAN)
endif
MLXFLAGS = -lX11 -lXext -lm

SRC_DIR = srcs
BUILD_DIR = .obj

SRC_FILE = main.c\
           game/game_new.c game/game_init.c game/game_run.c game/game_destroy.c game/game_handle.c  game/game_set.c\
		   layer/layer_clear.c layer/layer_create.c layer/layer_destroy.c layer/layer_dupe.c layer/layer_fill.c layer/layer_get_offset.c layer/layer_get_pixel.c layer/layer_set_offset.c layer/layer_set_pixel.c layer/layer_rotate.c layer/layer_volatile.c layer/layer_split_fill.c layer/layer_add_texture.c layer/layer_visible.c layer/layer_width.c layer/layer_mask.c\
		   layer/stack/layer_stack_add.c layer/stack/layer_stack_create.c layer/stack/layer_stack_destroy.c layer/stack/layer_stack_get.c layer/stack/layer_stack_render.c\
		   layer/group/layer_group_create.c layer/group/layer_group_destroy.c layer/group/layer_group_add.c layer/group/layer_group_get.c layer/group/layer_group_render.c layer/group/layer_group_get_depth.c\
		   draw/draw_circle_fill.c draw/draw_circle.c draw/draw_line.c draw/draw_rect_fill.c draw/draw_rect.c draw/draw_triangle_fill.c draw/draw_triangle.c draw/draw_xpm_texture.c draw/draw_text.c\
		   utils/int_to_pixel.c utils/pixel_create.c utils/pixel_to_int.c utils/prerr.c utils/math_utils_bonus.c utils/vector2.c\
		   raycast/ray.c raycast/ray_wall_hit.c raycast/ray_check_side.c  raycast/ray_animation.c\
		   view/view_create.c view/view_create_bonus.c view/view_init_bonus.c\
		   map/map_init.c map/map_draw_init.c map/map_init_pos.c\
		   hook/hook_display_mouse_move.c hook/hook_no_display_mouse_move.c hook/hook_release.c hook/hook_press.c\
		   player/player_move.c player/door_manager.c\
		   parsing/parsing.c parsing/parsing_map.c parsing/parsing_checks.c parsing/parsing_checks_utils.c parsing/set_textures.c parsing/convert_parsing.c parsing/parsing_header.c parsing/parsing_header_text_pix.c parsing/parsing_map_utils.c\

SRC_FILE_BONUS = main.c\
		   game/game_new.c game/game_init.c game/game_run.c game/game_destroy.c game/game_handle.c  game/game_set.c\
		   layer/layer_clear.c layer/layer_create.c layer/layer_destroy.c layer/layer_dupe.c layer/layer_fill.c layer/layer_get_offset.c layer/layer_get_pixel.c layer/layer_set_offset.c layer/layer_set_pixel.c layer/layer_rotate.c layer/layer_volatile.c layer/layer_split_fill.c layer/layer_add_texture.c layer/layer_visible.c layer/layer_width.c layer/layer_mask.c\
		   layer/stack/layer_stack_add.c layer/stack/layer_stack_create.c layer/stack/layer_stack_destroy.c layer/stack/layer_stack_get.c layer/stack/layer_stack_render.c\
		   layer/group/layer_group_create.c layer/group/layer_group_destroy.c layer/group/layer_group_add.c layer/group/layer_group_get.c layer/group/layer_group_render.c layer/group/layer_group_get_depth.c\
		   draw/draw_circle_fill.c draw/draw_circle.c draw/draw_line.c draw/draw_rect_fill.c draw/draw_rect.c draw/draw_triangle_fill.c draw/draw_triangle.c draw/draw_xpm_texture.c draw/draw_text.c\
		   utils/int_to_pixel.c utils/pixel_create.c utils/pixel_to_int.c utils/prerr.c utils/math_utils_bonus.c utils/vector2.c\
		   raycast/ray.c raycast/ray_wall_hit.c raycast/ray_check_side.c  raycast/ray_animation_bonus.c\
		   view/view_create.c view/view_create_bonus.c view/view_init_bonus.c\
		   map/map_init.c map/map_draw_init.c map/map_init_pos.c\
		   hook/hook_display_mouse_move.c hook/hook_no_display_mouse_move.c hook/hook_release.c hook/hook_press.c\
		   player/player_move.c player/door_manager.c\
		   parsing/parsing.c parsing/parsing_map.c parsing/parsing_checks_bonus.c parsing/parsing_checks_utils.c parsing/set_textures.c parsing/convert_parsing.c parsing/parsing_header.c parsing/parsing_header_text_pix.c parsing/parsing_map_utils.c\

SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILE))
SRC_BONUS = $(addprefix $(SRC_DIR)/, $(SRC_FILE_BONUS))

OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))
OBJ_BONUS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_BONUS))

ifdef BONUS
		OBJ = $(OBJ_BONUS)
		NAME = $(NAME_BONUS)
endif

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

bonus :
	$(MAKE) BONUS=1 all

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
	$(RM) $(NAME) $(NAME_BONUS) $(LIBMLXA)

re: fclean all
	
force:

.PHONY: all clean fclean re