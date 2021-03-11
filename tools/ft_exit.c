#include "cub3d.h"

static void		ft_mlx_destroy_all(t_mlx *m)
{
	int		i;

	if (m->wnd != NULL)
	{
		mlx_clear_window(m->mlx, m->wnd);
		mlx_destroy_window(m->mlx, m->wnd);
	}
	if (m->frame.img != NULL)
		mlx_destroy_image(m->mlx, m->frame.img);
	i = -1;
	while (++i < 5)
	{
		free(m->cfg->tpath[i]);
		if (m->tex[i].img != NULL)
			mlx_destroy_image(m->mlx, m->tex[i].img);
	}
}

static void		ft_freeall(t_mlx *m)
{
	int		i;

	ft_mlx_destroy_all(m);
	free(m->cfg->line);
	free(m->cfg->mapline);
	free(m->spr);
	free(m->bytes);
	free(m->cam->zdist);
	if (m->cfg->map != NULL)
	{
		i = 0;
		while (i < m->cfg->map_h)
			free(m->cfg->map[i++]);
		free(m->cfg->map);
	}
}

int				ft_exit(t_mlx *mlx)
{
	ft_freeall(mlx);
	exit(mlx->exitcode);
	return (0);
}
