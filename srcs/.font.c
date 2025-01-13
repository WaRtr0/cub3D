#include "font.h"
#include "../libft/libft.h"

void	free_glyph(t_glyph *glyph)
{
	int	i;

	if (!glyph)
		return ;
	if (glyph->bitmap)
	{
		i = 0;
		while (i < glyph->bbx_height)
		{
			if (glyph->bitmap[i])
				free(glyph->bitmap[i]);
			i++;
		}
		free(glyph->bitmap);
		glyph->bitmap = NULL;
	}
}


t_bdf   *font_init_bdf(void)
{
	t_bdf   *bdf;

	bdf = (t_bdf *)malloc(sizeof(t_bdf));
	if (!bdf)
		return (NULL);
	bdf->glyphs = (t_glyph *)malloc(sizeof(t_glyph) * INITIAL_GLYPH_CAPACITY);
	if (!bdf->glyphs)
	{
		free(bdf);
		return (NULL);
	}
	bdf->glyph_count = 0;
	bdf->glyph_capacity = INITIAL_GLYPH_CAPACITY;
	return (bdf);
}

int hex_char_to_int(char c)
{
	if (c >= '0' && c <= '9')
		return c - '0';
	else if (c >= 'A' && c <= 'F')
		return c - 'A' + 10;
	else if (c >= 'a' && c <= 'f')
		return c - 'a' + 10;
	else
		return -1;
}

#include <stdio.h>
unsigned char *hex_to_bytes(const char *hex_str, int *out_len)
{
	int len = ft_strlen(hex_str);
	int byte_len = (len + 1) / 2; // Arrondi vers le haut pour les longueurs impaires
	unsigned char *bytes = malloc(byte_len);
	int i = 0;
	int j = 0;

	if (!bytes)
		return NULL;

    // Si la longueur est impaire, on traite le premier caractère séparément
	if (len % 2 != 0)
	{
		int val = hex_char_to_int(hex_str[0]);
		if (val == -1)
		{
			free(bytes);
			return NULL; // Caractère hexadécimal invalide
		}
		bytes[j++] = val;
		i = 1;
	}

	for (; i < len; i += 2)
	{
		int high = hex_char_to_int(hex_str[i]);
		int low = hex_char_to_int(hex_str[i + 1]);

		if (high == -1 || low == -1)
		{
			free(bytes);
			printf("high: %d, low: %d\n", high, low);
			return NULL; // Caractère hexadécimal invalide
		}
        bytes[j++] = (high << 4) | low;
	}
	*out_len = byte_len;
	return bytes;
}


void    font_free_bdf(t_bdf *bdf)
{
	int i;

	if (!bdf)
		return;
	i = 0;
	while (i < bdf->glyph_count)
	{
		free_glyph(&(bdf->glyphs[i]));
		i++;
	}
	free(bdf->glyphs);
	free(bdf);
}

void    add_glyph(t_bdf *bdf, t_glyph glyph)
{
	t_glyph *new_glyphs;
	int	i;

	if (bdf->glyph_count >= bdf->glyph_capacity)
	{
		bdf->glyph_capacity *= 2;
		new_glyphs = (t_glyph *)malloc(sizeof(t_glyph) * bdf->glyph_capacity);
        if (!new_glyphs)
        {
            // printf("Failed to allocate memory for glyphs");
            exit(EXIT_FAILURE);
        }
        i = 0;
        while (i < bdf->glyph_count)
        {
            new_glyphs[i] = bdf->glyphs[i];
            i++;
        }
        free(bdf->glyphs);
        bdf->glyphs = new_glyphs;
    }
    bdf->glyphs[bdf->glyph_count] = glyph;
    bdf->glyph_count++;
}


int	parse_bdf_line(char *line, t_glyph *glyph)
{
	char	**parts;
	int		i;

	if (ft_strncmp(line, "ENCODING", 8) == 0)
		glyph->encoding = ft_atoi(line + 9);
	else if (ft_strncmp(line, "DWIDTH", 6) == 0)
		glyph->d_width = ft_atoi(line + 7);
	else if (ft_strncmp(line, "BBX", 3) == 0)
	{
		parts = ft_split(line + 4, ' ');
		if (parts)
		{
			glyph->bbx_width = ft_atoi(parts[0]);
			glyph->bbx_height = ft_atoi(parts[1]);
			glyph->bbx_x_offset = ft_atoi(parts[2]);
			glyph->bbx_y_offset = ft_atoi(parts[3]);
			i = 0;
			while (parts[i])
				free(parts[i++]);
			free(parts);
		}
		return (1);
	}
	return (0);
}

#include <stdio.h>
t_glyph	parse_glyph(int fd)
{
	t_glyph	glyph;
	char	*line;
	int		bitmap_started;
	int		i;

	ft_memset(&glyph, 0, sizeof(t_glyph));
	bitmap_started = 0;
	while ((line = get_next_line(fd)))
	{
		if (ft_strncmp(line, "ENDCHAR", 7) == 0)
		{
			free(line);
			break ;
		}
		if (bitmap_started)
		{
			if (i < glyph.bbx_height)
			{
				int	byte_len;
                size_t len = ft_strlen(line);
                if (len > 0 && line[len - 1] == '\n')
                    line[len - 1] = '\0';
                printf("line: %s\n", line);
				glyph.bitmap[i] = hex_to_bytes(line, &byte_len);
                printf("byte_len: %d\n", byte_len);
				i++;
			}
		}
		else if (ft_strncmp(line, "BITMAP", 6) == 0)
		{
			bitmap_started = 1;
			i = 0;
			glyph.bitmap = malloc(sizeof(unsigned char *) * glyph.bbx_height);
			if (!glyph.bitmap)
			{
				free(line);
				return (glyph);
			}
		}
		else
			parse_bdf_line(line, &glyph);
		free(line);
	}
	return (glyph);
}



int     font_parse_bdf(const char *filename, t_bdf *bdf)
{
    int     fd;
    char    *line;
    t_glyph glyph;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (1);
    while ((line = get_next_line(fd)))
    {
        if (ft_strncmp(line, "STARTCHAR", 9) == 0)
        {
            glyph = parse_glyph(fd);
            add_glyph(bdf, glyph);
        }
        free(line);
    }
    close(fd);
    return (0);
}

