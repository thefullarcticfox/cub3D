#include "cub3d.h"
#include <sys/stat.h>

static void		ft_itobytes(int num, unsigned char *arr)
{
	arr[0] = (unsigned char)(num & 0xFF);
	arr[1] = (unsigned char)((num >> 8) & 0xFF);
	arr[2] = (unsigned char)((num >> 16) & 0xFF);
	arr[3] = (unsigned char)((num >> 24) & 0xFF);
}

static void		ft_bmpheader(t_mlx *m, int bmpsize)
{
	int			pixels_per_meter;

	ft_bzero(m->bytes, 54);
	ft_memcpy(m->bytes, "BM", 2);
	ft_itobytes(bmpsize, m->bytes + 2);
	m->bytes[10] = (unsigned char)54;
	m->bytes[14] = (unsigned char)40;
	ft_itobytes(m->res_x, m->bytes + 18);
	ft_itobytes(m->res_y, m->bytes + 22);
	m->bytes[26] = (unsigned char)1;
	m->bytes[28] = (unsigned char)32;
	m->bytes[34] = (unsigned char)32;
	pixels_per_meter = (int)((double)SCREENSHOT_DPI * 39.37);
	ft_itobytes(pixels_per_meter, m->bytes + 38);
	ft_itobytes(pixels_per_meter, m->bytes + 42);
}

static void		ft_bmpimage(t_mlx *m, int bmpsize)
{
	int		i;
	int		x;
	int		y;

	i = 54;
	y = m->res_y;
	while (y-- > 0)
	{
		x = -1;
		while (++x < m->res_x && i < bmpsize)
		{
			ft_itobytes(m->frame.addr[y * m->res_x + x], m->bytes + i);
			i += 4;
		}
	}
}

void			ft_bmp(t_mlx *m)
{
	int		bmpfd;
	int		bmpsize;

	bmpfd = open("./screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC | O_APPEND,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (bmpfd < 0)
		ft_error(m, -1, "Failed to create or overwrite ./screenshot.bmp");
	ft_render(m);
	bmpsize = m->res_x * m->res_y * 4 + 54;
	m->bytes = (unsigned char *)malloc(sizeof(unsigned char) * bmpsize);
	if (m->bytes == NULL)
		ft_error(m, -1, "Screenshot render");
	ft_bmpheader(m, bmpsize);
	ft_bmpimage(m, bmpsize);
	if (write(bmpfd, m->bytes, bmpsize) < bmpsize)
		ft_error(m, -1, "Failed to write screenshot file");
	free(m->bytes);
	m->bytes = NULL;
	close(bmpfd);
	ft_putendl_fd("Screenshot saved to ./screenshot.bmp", 1);
	ft_exit(m);
}
