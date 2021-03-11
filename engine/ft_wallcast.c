#include "cub3d.h"

static t_wall	ft_definewall(t_mlx *m, t_cam *c, int x)
{
	t_wall	w;

	w.line_height = (int)(m->res_y / c->zdist[x]);
	w.drawstart = -w.line_height / 2 + m->res_y / 2;
	w.drawend = w.line_height / 2 + m->res_y / 2;
	if (w.drawstart < 0)
		w.drawstart = 0;
	if (w.drawend > m->res_y)
		w.drawend = m->res_y;
	if (c->side == 0 || c->side == 3)
		w.wall_x = c->pos_y + c->zdist[x] * c->raydir_y;
	else
		w.wall_x = c->pos_x + c->zdist[x] * c->raydir_x;
	w.tex_x = (int)((w.wall_x - floor(w.wall_x)) *
		(double)m->tex[c->side].width);
	if ((c->side == 0 || c->side == 3) && c->raydir_x > 0)
		w.tex_x = m->tex[c->side].width - w.tex_x - 1;
	if ((c->side == 1 || c->side == 2) && c->raydir_y < 0)
		w.tex_x = m->tex[c->side].width - w.tex_x - 1;
	w.tex_step = 1.0 * m->tex[c->side].height / w.line_height;
	w.tex_pos = (w.drawstart - m->res_y / 2 + w.line_height / 2) * w.tex_step;
	return (w);
}

void			ft_wallcast(t_mlx *m, t_cam *c, int **out)
{
	t_wall	w;
	int		x;
	int		y;

	x = -1;
	while (++x < m->res_x)
	{
		ft_raycast(m, c, x);
		w = ft_definewall(m, c, x);
		y = w.drawstart - 1;
		while (++y < w.drawend)
		{
			w.tex_y = (int)floor(w.tex_pos);
			if (w.tex_y < 0)
				w.tex_y = 0;
			if (w.tex_y > m->tex[c->side].height - 1)
				w.tex_y = m->tex[c->side].height - 1;
			(*out)[y * m->res_x + x] = m->tex[c->side].addr[w.tex_y *
				m->tex[c->side].width + w.tex_x];
			w.tex_pos += w.tex_step;
		}
	}
}
