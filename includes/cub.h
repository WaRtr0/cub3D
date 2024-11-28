
#ifndef CUB_H
# define CUB_H


// Raycasting
# define FOV 60
# define RAYMODE 0
// 0 = Raycast
// 1 = Raycast by step
// 2 = Raycast by Dichotomy
// 10 = Raymarching

# define RAYSTEP 4

// Window
# define HEIGHT 100
# define WIDTH 100
# define SPLIT_HEIGHT (-(HEIGHT / 2))

// Math
# define M_PI 3.14159265358979323846

# define WALL_HEIGHT 1
# define HIT_BOX 0.01
# define SPEED 0.1

// Scale
# define SCALE_2D 32
# define SCALE_3D ((WIDTH / 2) / tan((FOV / 2) * M_PI / 180) * WALL_HEIGHT)

// Mouse
# define YAW_MAX 360
# define YAW_MIN 0
# define PITCH_MAX 50
# define SENTIVITY 0.5

#endif
