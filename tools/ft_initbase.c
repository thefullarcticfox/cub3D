#include "cub3d.h"

void		ft_initcfg(t_cfg *cfg)
{
	int		i;

	cfg->line = NULL;
	cfg->mapline = NULL;
	i = -1;
	while (++i < 5)
		cfg->tpath[i] = NULL;
	cfg->f_argb = -1;
	cfg->c_argb = -1;
	cfg->map = NULL;
	cfg->map_h = -1;
	cfg->map_w = -1;
	cfg->start_x = -1;
	cfg->start_y = -1;
	cfg->start_dir = '\0';
	cfg->bmp = 0;
}

void		ft_initbase(t_mlx *m)
{
	int		i;

	m->mlx = NULL;
	m->wnd = NULL;
	m->spr = NULL;
	m->bytes = NULL;
	m->res_x = -1;
	m->res_y = -1;
	i = -1;
	while (++i < 5)
	{
		m->tex[i].img = NULL;
		m->tex[i].addr = NULL;
	}
	m->frame.img = NULL;
	m->frame.addr = NULL;
	ft_initcfg(m->cfg);
	m->cam->zdist = NULL;
}
