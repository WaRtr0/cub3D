
#ifndef CUB_H
# define CUB_H


// Raycasting
# ifndef FOV
# define FOV 60
# endif
# define RAYMODE 0
// 0 = Raycast
// 1 = Raycast by step
// 2 = Raycast by Dichotomy
// 10 = Raymarching

# define RAYSTEP 4

// Window
# ifndef HEIGHT
#  define HEIGHT 540
# endif

# ifndef WIDTH
#  define WIDTH 960
# endif


# define OUTPUT_HEIGHT 540
# define OUTPUT_WIDTH 960
# define RATIO 1

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
# define SPEED 1
# define STEP 0.03

# define ENABLE_TRANSPARENCY 1

// Scale
# define SCALE_2D 32
# define SCALE_3D (((WIDTH / 2) / tan((FOV / 2) * M_PI / 180)) * WALL_HEIGHT)

// Mouse
# define YAW_MAX 360
# define YAW_MIN 0
# define PITCH_MAX 50
# define SENTIVITY 0.25

# define DEBUG 0
# define MAX_FRAME 60

#endif
