
#ifndef CUB_H
# define CUB_H


// Raycasting

# define GAME_NAME "My Game !"
# ifndef FOV
# define FOV 60
# endif
# define RAYMODE 0
// 0 = Raycast
// 1 = Raycast by step
// 2 = Raycast by Dichotomy
// 10 = Raymarching

# define RAYSTEP 4


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

# define OUTPUT_HEIGHT 1080
# define OUTPUT_WIDTH 1920
# define RATIO 2


# define CEIL_BONUS 1

// Window
# ifndef HEIGHT
#  define HEIGHT (OUTPUT_HEIGHT / RATIO)
# endif

# ifndef WIDTH
#  define WIDTH (OUTPUT_WIDTH / RATIO)
# endif

# if HEIGHT < 64
#  define HEIGHT 64
# endif

# if HEIGHT > 2160
#  define HEIGHT 2160
# endif


# if WIDTH < 64
#  define WIDTH 64
# endif

# if WIDTH > 3840
#  define WIDTH 3840
# endif

# if FOV > 120
#  define FOV 120
# endif

# if FOV < 30
#  define FOV 30
# endif

# define SPLIT_HEIGHT (-(HEIGHT / 2))

# define HEIGHT_PERC ( HEIGHT / 100)
// Math
# define M_PI 3.14159265358979323846
// # define M_PI 3.14

# define WALL_HEIGHT 1
# define HIT_BOX 0.25
# define DOOR_HIT_BOX 0.05
// # define SPEED 1
# define SPEED 0.1
// # define STEP 0.03
# define STEP 0.1
# define DOOR_STEP 0.05

# define ENABLE_TRANSPARENCY 1

// Scale
# define SCALE_2D (32 / RATIO)
// # define SCALE_3D (((WIDTH / 2) / tan((FOV / 2) * M_PI / 180)) * WALL_HEIGHT)

// Map

# define MAP_SIZE_RATIO 1
# define MAP_SIZE ((250 * MAP_SIZE_RATIO) / RATIO)

// Mouse
# define YAW_MAX 360
# define YAW_MIN 0
# define PITCH_MAX 50
# define SENTIVITY 0.25

# define DEBUG 0
# define MAX_FRAME 180

#define FLOOR_TEXTURE 70
#define CEILING_TEXTURE 71
#define SIZE_TEXTURE 64


#endif
