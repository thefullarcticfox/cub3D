#include "cub3d.h"

static void		ft_move(t_cam *c, t_cfg *f, int dir)
{
	double	x;
	double	y;

	x = c->pos_x + c->dir_x * MSPD * dir;
	y = c->pos_y + c->dir_y * MSPD * dir;
	if ((int)floor(x) < 0)
		x = (double)0;
	if ((int)floor(y) < 0)
		y = (double)0;
	if ((int)floor(x) > f->map_h - 1)
		x = (double)(f->map_h - 1);
	if ((int)floor(y) > f->map_w - 1)
		y = (double)(f->map_w - 1);
	if (f->map[(int)floor(x)][(int)floor(c->pos_y)] != '1')
		c->pos_x = x;
	if (f->map[(int)floor(c->pos_x)][(int)floor(y)] != '1')
		c->pos_y = y;
	if (f->map[(int)floor(c->pos_x)][(int)floor(c->pos_y)] == '2')
		f->map[(int)floor(c->pos_x)][(int)floor(c->pos_y)] = 0;
}

static void		ft_strafe(t_cam *c, t_cfg *f, int dir)
{
	double	x;
	double	y;

	x = c->pos_x - c->dir_y * MSPD * dir;
	y = c->pos_y + c->dir_x * MSPD * dir;
	if ((int)floor(x) < 0)
		x = (double)0;
	if ((int)floor(y) < 0)
		y = (double)0;
	if ((int)floor(x) > f->map_h - 1)
		x = (double)(f->map_h - 1);
	if ((int)floor(y) > f->map_w - 1)
		y = (double)(f->map_w - 1);
	if (f->map[(int)floor(x)][(int)floor(c->pos_y)] != '1')
		c->pos_x = x;
	if (f->map[(int)floor(c->pos_x)][(int)floor(y)] != '1')
		c->pos_y = y;
	if (f->map[(int)floor(c->pos_x)][(int)floor(c->pos_y)] == '2')
		f->map[(int)floor(c->pos_x)][(int)floor(c->pos_y)] = 0;
}

static void		ft_rotate(t_cam *c, int dir)
{
	double	odir_x;
	double	oplane_x;

	odir_x = c->dir_x;
	oplane_x = c->plane_x;
	c->dir_x = odir_x * cos(RSPD * dir) - c->dir_y * sin(RSPD * dir);
	c->dir_y = odir_x * sin(RSPD * dir) + c->dir_y * cos(RSPD * dir);
	c->plane_x = oplane_x * cos(RSPD * dir) - c->plane_y * sin(RSPD * dir);
	c->plane_y = oplane_x * sin(RSPD * dir) + c->plane_y * cos(RSPD * dir);
}

int				ft_control(int key, t_mlx *m)
{
	if (key == KEY_W)
		ft_move(m->cam, m->cfg, 1);
	if (key == KEY_S)
		ft_move(m->cam, m->cfg, -1);
	if (key == KEY_A)
		ft_strafe(m->cam, m->cfg, 1);
	if (key == KEY_D)
		ft_strafe(m->cam, m->cfg, -1);
	if (key == KEY_LEFT)
		ft_rotate(m->cam, 1);
	if (key == KEY_RIGHT)
		ft_rotate(m->cam, -1);
	if (key == KEY_ESC)
		ft_exit(m);
	return (0);
}
