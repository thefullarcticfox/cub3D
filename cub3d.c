#include "cub3d.h"

static void		ft_validateargs(t_mlx *mlx, int argc, char **argv)
{
	if (argc < 2)
		ft_error(mlx, 0, NULL);
	else
	{
		if (ft_strlen(argv[1]) < 5 ||
			ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 5) != 0)
			ft_error(mlx, 1, argv[1]);
		if (argc == 3 && ft_strncmp(argv[2], "--save", 7) == 0)
			mlx->cfg->bmp = 1;
		else if (argc != 2)
			ft_error(mlx, 13, NULL);
		if ((mlx->cfg->fd = open(argv[1], O_RDONLY)) < 0)
			ft_error(mlx, -1, argv[1]);
	}
}

static void		ft_runmlx(t_mlx *m)
{
	if ((m->mlx = mlx_init()) == NULL)
		ft_error(m, 17, NULL);
	ft_fitresolution(m);
	if ((unsigned long)4 * m->res_x * m->res_y + 54 > 2147483647)
		ft_error(m, 22, NULL);
	ft_initcam(m);
	ft_loadtextures(m);
	if (m->cfg->bmp)
		ft_bmp(m);
	else
		ft_window(m);
}

int				main(int argc, char **argv)
{
	t_mlx		mlx;
	t_cfg		cfg;
	t_cam		cam;

	mlx.exitcode = 0;
	mlx.cfg = &cfg;
	mlx.cam = &cam;
	ft_initbase(&mlx);
	ft_validateargs(&mlx, argc, argv);
	ft_parsecfg(&mlx, &cfg);
	ft_runmlx(&mlx);
	return (0);
}
