#ifndef H_FONT
# define H_FONT

# include "types.h"
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define INITIAL_GLYPH_CAPACITY 128

typedef struct s_glyph
{
	int		encoding;
	int		bbx_width;
	int		bbx_height;
	int		bbx_x_offset;
	int		bbx_y_offset;
	int		d_width;
    unsigned char **bitmap;
}			t_glyph;

typedef struct s_bdf
{
	t_glyph	*glyphs;
	int		glyph_count;
	int		glyph_capacity;
}			t_bdf;

typedef struct s_font
{
	t_bdf	*bdf;
	int		size;
	t_pixel	color;
}			t_font;

t_bdf		*font_init_bdf(void);
void		font_free_bdf(t_bdf *bdf);
int			font_parse_bdf(const char *filename, t_bdf *bdf);

#endif