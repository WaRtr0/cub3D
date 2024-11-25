NAME = cub3d
CC = cc

RM = rm -rf

INCLUDES_DIR 	= includes

INCLUDES = $(INCLUDES_DIR)/game.h\
		   $(INCLUDES_DIR)/layer.h\
		   $(INCLUDES_DIR)/types.h\
		   $(INCLUDES_DIR)/hook.h\
		   $(INCLUDES_DIR)/draw.h\
		   $(INCLUDES_DIR)/font.h\
		   $(INCLUDES_DIR)/view.h\
		   $(INCLUDES_DIR)/parsing.h\
		   $(INCLUDES_DIR)/utils.h\

CFLAGS = -g3
MLXFLAGS = -lX11 -lXext -lm -g3

SRC_DIR = srcs
BUILD_DIR = .obj

SRC_FILE = main.c\
           game.c\
		   layer.c\
		   draw.c\
		   font.c\
		   view.c\
		   parsing.c\
		   parsing_map.c\
		   parsing_checks.c\
		   utils.c\

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

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.c $(INCLUDES)
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