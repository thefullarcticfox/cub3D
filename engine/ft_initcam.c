#include "cub3d.h"

static void		ft_initdir(t_cam *cam, t_cfg *cfg)
{
	if (cfg->start_dir == 'N')
	{
		cam->dir_x = -1.0;
		cam->dir_y = 0.0;
	}
	if (cfg->start_dir == 'E')
	{
		cam->dir_x = 0.0;
		cam->dir_y = 1.0;
	}
	if (cfg->start_dir == 'W')
	{
		cam->dir_x = 0.0;
		cam->dir_y = -1.0;
	}
	if (cfg->start_dir == 'S')
	{
		cam->dir_x = 1.0;
		cam->dir_y = 0.0;
	}
}

static void		ft_initplane(t_cam *cam, t_cfg *cfg)
{
	if (cfg->start_dir == 'N')
	{
		cam->plane_x = 0.0;
		cam->plane_y = 1.0;
	}
	if (cfg->start_dir == 'E')
	{
		cam->plane_x = 1.0;
		cam->plane_y = 0.0;
	}
	if (cfg->start_dir == 'W')
	{
		cam->plane_x = -1.0;
		cam->plane_y = 0.0;
	}
	if (cfg->start_dir == 'S')
	{
		cam->plane_x = 0.0;
		cam->plane_y = -1.0;
	}
	cam->plane_x *= tan(FOV / 2.0 * M_PI / 180.0);
	cam->plane_y *= tan(FOV / 2.0 * M_PI / 180.0);
}

void			ft_initcam(t_mlx *m)
{
	ft_countsprites(m->cfg, m->cfg->map);
	if (m->cfg->spr_num > 0)
	{
		m->spr = (t_spr *)malloc(sizeof(t_spr) * m->cfg->spr_num);
		if (m->spr == NULL)
			ft_error(m, -1, "Sprites array");
	}
	m->cam->pos_x = (double)m->cfg->start_x + 0.5;
	m->cam->pos_y = (double)m->cfg->start_y + 0.5;
	ft_initdir(m->cam, m->cfg);
	ft_initplane(m->cam, m->cfg);
	m->cam->zdist = (double *)malloc(sizeof(double) * m->res_x);
	if (m->cam->zdist == NULL)
		ft_error(m, -1, "Z-distance buffer");
}
