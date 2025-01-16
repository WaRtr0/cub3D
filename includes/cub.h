#ifndef CUB_H
# define CUB_H

# define GAME_NAME "My Cub3D !"
# ifndef FOV
#  define FOV 60
# endif

# if FOV > 120
#  undef FOV
#  define FOV 120
# endif

# if FOV < 30
#  undef FOV
#  define FOV 30
# endif

// resolution size
// QQVGA 160 x 120
// QVGA 320 x 240
// VGA 640 x 480
// SVGA 800 x 600
// XGA 1024 x 768
// HD 1280 x 720
// HD 1366 x 768
// mac 1440 x 900
// HD 1600 x 900
// FHD 1920 x 1080
// 2K 2560 x 1440
// 4K 3840 x 2160

# define NO_DISPLAY_MOUSE 1
# define AUTO_CENTER_MOUSE 1

# ifndef OUTPUT_HEIGHT
#  define OUTPUT_HEIGHT 1080
# endif

# ifndef OUTPUT_WIDTH
#  define OUTPUT_WIDTH 1920
# endif

# ifndef RATIO
#  define RATIO 2
# endif

# if OUTPUT_HEIGHT % RATIO != 0
#  error "OUTPUT_HEIGHT must be a multiple of RATIO"
# endif

# if OUTPUT_WIDTH % RATIO != 0
#  error "OUTPUT_WIDTH must be a multiple of RATIO"
# endif

// 0.1 <-> 0.5
# define HIT_BOX 0.25


# define CEIL_BONUS 1

// map
# define MAP_OFFSET 25
# define MIN_WIDTH 550
# define MAP_SIZE_RATIO 1

// Math
# define M_PI 3.14159265358979323846
# define M_RAD 0.017453292519943295

# define STEP 0.1 //speed

# define WALL_HEIGHT 1.0


# define DOOR_HIT_BOX 0.05
# define DOOR_STEP 0.05

# define ENABLE_TRANSPARENCY 0

// Scale
# define SIZE_2D 32
// # define SCALE_2D (SIZE_2D / RATIO)
// # define SCALE_3D (((WIDTH / 2) / tan((FOV / 2) * M_PI / 180)) * WALL_HEIGHT)

// Mouse
# define YAW_MAX 360
# define YAW_MIN 0
# define PITCH_MAX 50
# define SENTIVITY 0.25

# define DEBUG 0
# define MAX_FRAME 1800

# define CEILING_TEXTURE 70
# define FLOOR_TEXTURE 71
// # define CEIL "./assets/textures/ceiling.xpm"
# define CEIL "./assets/doom/ceil.xpm"
// # define FLOOR "./assets/textures/ceiling.xpm"
# define FLOOR "./assets/doom/floor.xpm"

#endif
