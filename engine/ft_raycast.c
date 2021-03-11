#include "cub3d.h"

static void		ft_setrayvect(t_cam *c, t_ray *r)
{
	c->raydir_x = c->dir_x + c->plane_x * r->cam_x;
	c->raydir_y = c->dir_y + c->plane_y * r->cam_x;
	r->map_x = (int)floor(c->pos_x);
	r->map_y = (int)floor(c->pos_y);
	r->deltadist_x = fabs(1 / c->raydir_x);
	r->deltadist_y = fabs(1 / c->raydir_y);
}

static t_ray	ft_defineray(t_mlx *m, t_cam *c, int x)
{
	t_ray	r;

	r.cam_x = 2 * x / (double)m->res_x - 1;
	ft_setrayvect(c, &r);
	if (c->raydir_x < 0)
	{
		r.step_x = -1;
		r.sidedist_x = (c->pos_x - r.map_x) * r.deltadist_x;
	}
	else
	{
		r.step_x = 1;
		r.sidedist_x = (r.map_x + 1.0 - c->pos_x) * r.deltadist_x;
	}
	if (c->raydir_y < 0)
	{
		r.step_y = -1;
		r.sidedist_y = (c->pos_y - r.map_y) * r.deltadist_y;
	}
	else
	{
		r.step_y = 1;
		r.sidedist_y = (r.map_y + 1.0 - c->pos_y) * r.deltadist_y;
	}
	return (r);
}

static void		ft_sendray(t_cam *c, t_ray *r)
{
	if (r->sidedist_x < r->sidedist_y)
	{
		r->sidedist_x += r->deltadist_x;
		r->map_x += r->step_x;
		if (r->step_x < 0)
			c->side = 0;
		else
			c->side = 3;
	}
	else
	{
		r->sidedist_y += r->deltadist_y;
		r->map_y += r->step_y;
		if (r->step_y < 0)
			c->side = 1;
		else
			c->side = 2;
	}
}

void			ft_raycast(t_mlx *m, t_cam *c, int x)
{
	t_ray	r;

	r = ft_defineray(m, c, x);
	while (1)
	{
		ft_sendray(c, &r);
		if (m->cfg->map[r.map_x][r.map_y] == '1')
			break ;
		if (m->cfg->map[r.map_x][r.map_y] == '2')
			ft_addsprite(m, c, r);
	}
	if (c->side == 0 || c->side == 3)
		c->zdist[x] = (r.map_x - c->pos_x + (1 - r.step_x) / 2) / c->raydir_x;
	else
		c->zdist[x] = (r.map_y - c->pos_y + (1 - r.step_y) / 2) / c->raydir_y;
}
