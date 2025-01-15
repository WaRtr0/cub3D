#ifndef HOOK_H
# define HOOK_H

# include "types.h"

# define KEY_A 97
# define KEY_B 98
# define KEY_C 99
# define KEY_D 100
# define KEY_E 101
# define KEY_F 102
# define KEY_G 103
# define KEY_H 104
# define KEY_I 105
# define KEY_J 106
# define KEY_K 107
# define KEY_L 108
# define KEY_M 109
# define KEY_N 110
# define KEY_O 111
# define KEY_P 112
# define KEY_Q 113
# define KEY_R 114
# define KEY_S 115
# define KEY_T 116
# define KEY_U 117
# define KEY_V 118
# define KEY_W 119
# define KEY_X 120
# define KEY_Y 121
# define KEY_Z 122

# define KEY_LEFT 65361
# define KEY_UP 65362
# define KEY_RIGHT 65363
# define KEY_DOWN 65364

# define KEY_ESC 65307

# define KEY_SPACE 32

# define KEY_SHIFT 65505
# define KEY_ALTGR 65514
# define KEY_CMD_LEFT 65507
# define KEY_CMD_RIGHT 65508
# define KEY_CTRL_LEFT 65506
# define KEY_CTRL_RIGHT 65508
# define KEY_SHIFT_LEFT 65505
# define KEY_SHIFT_RIGHT 65506
# define KEY_ALT_LEFT 65513
# define KEY_ALT_RIGHT 65514
# define KEY_FN 65384
# define KEY_CAPS 65509
# define KEY_TAB 65289
# define KEY_ENTER 65293
# define KEY_BACKSPACE 65288
# define KEY_DEL 65535
# define KEY_HOME 65360
# define KEY_END 65367
# define KEY_PAGE_UP 65365
# define KEY_PAGE_DOWN 65366
# define KEY_INSERT 65379
# define KEY_PRINT 65377
# define KEY_SCROLL 65300
# define KEY_PAUSE 65299
# define KEY_MENU 65383
# define KEY_HELP 65381
# define KEY_BREAK 65291
# define KEY_SYSREQ 65301
# define KEY_CLEAR 65291
# define KEY_SELECT 65376
# define KEY_AGAIN 65382
# define KEY_UNDO 65383
# define KEY_CUT 65389

# define KEY_SUPER 65515
# define KEY_HYPER 65516

# define KEY_F1 65470
# define KEY_F2 65471
# define KEY_F3 65472
# define KEY_F4 65473
# define KEY_F5 65474
# define KEY_F6 65475
# define KEY_F7 65476
# define KEY_F8 65477
# define KEY_F9 65478
# define KEY_F10 65479
# define KEY_F11 65480
# define KEY_F12 65481

# define KEY_NUM_0 65456
# define KEY_NUM_1 65457
# define KEY_NUM_2 65458
# define KEY_NUM_3 65459
# define KEY_NUM_4 65460
# define KEY_NUM_5 65461
# define KEY_NUM_6 65462
# define KEY_NUM_7 65463
# define KEY_NUM_8 65464
# define KEY_NUM_9 65465

# define KEY_NUM_ADD 65451
# define KEY_NUM_SUB 65453
# define KEY_NUM_MUL 65450
# define KEY_NUM_DIV 65455
# define KEY_NUM_ENTER 65421
# define KEY_NUM_DOT 65439
# define KEY_NUM_LOCK 65407

# define KEY_1 49
# define KEY_2 50
# define KEY_3 51
# define KEY_4 52
# define KEY_5 53
# define KEY_6 54
# define KEY_7 55
# define KEY_8 56
# define KEY_9 57
# define KEY_0 48

# define KEY_MINUS 45
# define KEY_EQUAL 61

# define KEY_BRACKET_LEFT 91
# define KEY_BRACKET_RIGHT 93
# define KEY_SEMICOLON 59
# define KEY_QUOTE 39
# define KEY_COMMA 44
# define KEY_DOT 46
# define KEY_SLASH 47
# define KEY_BACKSLASH 92
# define KEY_TILDE 96

typedef enum e_keyhook_event
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSE_DOWN = 4,
	ON_MOUSE_UP = 5,
	ON_MOUSE_MOVE = 6,
	ON_ENTER_NOTIFY = 7,
	ON_LEAVE_NOTIFY = 8,
	ON_FOCUS_IN = 9,
	ON_FOCUS_OUT = 10,
	ON_MAP_PRESS_NOTIFY = 11,
	ON_EXPOSE = 12,
	ON_GRAPHICS_EXPOSE = 13,
	ON_NOEXPOSE = 14,
	ON_VISIBILITY_NOTIFY = 15,
	ON_CREATE_NOTIFY = 16,
	ON_DESTROY_NOTIFY = 17,
	ON_UNMAP_NOTIFY = 18,
	ON_MAP_NOTIFY = 19,
	ON_MAP_REQUEST = 20,
	ON_REPARENT_NOTIFY = 21,
	ON_CONFIGURE_NOTIFY = 22,
	ON_CONFIGURE_REQUEST = 23,
	ON_GRAVITY_NOTIFY = 24,
	ON_RESIZE_REQUEST = 25,
	ON_CIRCULATE_NOTIFY = 26,
	ON_CIRCULATE_REQUEST = 27,
	ON_PROPERTY_NOTIFY = 28,
	ON_SELECTION_CLEAR = 29,
	ON_SELECTION_REQUEST = 30,
	ON_SELECTION_NOTIFY = 31,
	ON_COLORMAP_NOTIFY = 32,
	ON_CLIENT_MESSAGE = 33,
	ON_MAPPING_NOTIFY = 34,
	ON_GENERIC_EVENT = 35,
	ON_LAST_EVENT = 36
}	t_keyhook_event;

typedef enum e_keyhook_mask
{
	MASK_NO_EVENT = 0,
	MASK_KEY_PRESS = 1L<<0,
	MASK_KEY_RELEASE = 1L<<1,
	MASK_BUTTON_PRESS = 1L<<2,
	MASK_BUTTON_RELEASE = 1L<<3,
	MASKK_ENTER_WINDOW = 1L<<4,
	MASK_LEAVE_WINDOW = 1L<<5,
	MASK_POINTER_MOTION = 1L<<6,
	MASK_POINTER_MOTION_HINT = 1L<<7,
	MASK_LEFT_CLICK = 1L<<8,
	MASK_RIGHT_CLICK = 1L<<9,
	MASK_MIDDLE_CLICK= 1L<<10,
	MASK_SCOLL_UP = 1L<<11,
	MASK_SCROLL_DOWN = 1L<<12,
	MASK_BUTTON_MOTION = 1L<<13,
	MASK_KEYMAP_STATE = 1L<<14,
	MASK_EXPOSURE = 1L<<15,
	MASK_VISIBILITY_CHANGE = 1L<<16,
	MASK_STRUCTURE_NOTIFY = 1L<<17,
	MASK_RESIZE_REDIRECT = 1L<<18,
	MASK_SUBSTRUCTURE_NOTIFY = 1L<<19,
	MASK_SUBSTRUCTURE_REDIRECT = 1L<<20,
	MASK_FOCUS_CHANGE = 1L<<21,
	MASK_PROPERTY_CHANGE = 1L<<22,
	MASK_COLOR_MAP_CHANGE = 1L<<23,
	MASK_OWNER_GRAB_BUTTON = 1L<<24
}	t_keyhook_mask;

typedef struct s_triangle_points
{
	t_dvector2	center;
	t_dvector2	pos1;
	t_dvector2	pos2;
	t_dvector2	pos3;
}	t_triangle_points;

void	hook_no_display_mouse_move(int x, int y, t_game *game);
void	hook_display_mouse_move(int x, int y, t_game *game);
void	hook_release(int keycode, t_game *game);
void	hook_press(int keycode, t_game *game);

#endif
