#include "cub3d.h"

static void		ft_printerr1(int errnum)
{
	if (errnum == 0)
		ft_putendl_fd("No map file specified", 2);
	else if (errnum == 1)
		ft_putendl_fd("Wrong map file extension", 2);
	else if (errnum == 2)
		ft_putendl_fd("Undefined key or symbols before map", 2);
	else if (errnum == 3)
		ft_putendl_fd("Map is not rectangle or too small to spawn", 2);
	else if (errnum == 4)
		ft_putendl_fd("Map is not closed/surrounded by walls", 2);
	else if (errnum == 5)
		ft_putendl_fd("Invalid resolution", 2);
	else if (errnum == 6)
		ft_putendl_fd("Invalid RGB color", 2);
	else if (errnum == 7)
		ft_putendl_fd("No texture path specified", 2);
	else if (errnum == 8)
		ft_putendl_fd("Undefined symbols in or after map", 2);
	else if (errnum == 9)
		ft_putendl_fd("Duplicate key in map file", 2);
	else if (errnum == 10)
		ft_putendl_fd("Not enough keys in map file", 2);
}

static void		ft_printerr2(int errnum)
{
	if (errnum < 11)
		ft_printerr1(errnum);
	else if (errnum == 11)
		ft_putendl_fd("More than one player start position in map", 2);
	else if (errnum == 12)
		ft_putendl_fd("No player start position in map", 2);
	else if (errnum == 13)
		ft_putendl_fd("Unknown argument", 2);
	else if (errnum == 14)
		ft_putendl_fd("Wrong texture file extension (xpm images only)", 2);
	else if (errnum == 15)
		ft_putendl_fd("Bad texture/sprite resolution", 2);
	else if (errnum == 16)
		ft_putendl_fd("mlx_xpm_to_image failed", 2);
	else if (errnum == 17)
		ft_putendl_fd("mlx_init failed", 2);
	else if (errnum == 18)
		ft_putendl_fd("mlx_new_window failed", 2);
	else if (errnum == 19)
		ft_putendl_fd("mlx_new_image failed", 2);
	else if (errnum == 20)
		ft_putendl_fd("mlx_get_data_addr failed", 2);
}

static void		ft_printerr(int errnum)
{
	if (errnum < 21)
		ft_printerr2(errnum);
	else if (errnum == 21)
		ft_putendl_fd("No map in map file", 2);
	else if (errnum == 22)
		ft_putendl_fd("Resolution is too big to render", 2);
}

void			ft_error(t_mlx *mlx, int errnum, char *filename)
{
	ft_putendl_fd("Error", 2);
	if (filename != NULL)
	{
		if (ft_strlen(filename) > 0)
		{
			ft_putstr_fd(filename, 2);
			ft_putstr_fd(": ", 2);
		}
	}
	if (errnum >= 0)
		ft_printerr(errnum);
	else
		ft_putendl_fd(strerror(errno), 2);
	mlx->exitcode = 1;
	ft_exit(mlx);
}
