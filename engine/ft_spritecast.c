#include "cub3d.h"

static t_spr	ft_definespr(t_spr spr, t_cam *c, t_mlx *m)
{
	double	inverse;

	spr.x = spr.x - c->pos_x;
	spr.y = spr.y - c->pos_y;
	inverse = 1.0 / (c->plane_x * c->dir_y - c->plane_y * c->dir_x);
	spr.tf_x = inverse * (c->dir_y * spr.x - c->dir_x * spr.y);
	spr.tf_y = inverse * (-c->plane_y * spr.x + c->plane_x * spr.y);
	spr.scr_x = (int)((m->res_x / 2) * (1 + spr.tf_x / spr.tf_y));
	spr.height = abs((int)(m->res_y / spr.tf_y)) / SPR_SCALE_DIV;
	spr.drawstart_y = -(spr.height) / 2 + m->res_y / 2 +
		(int)(SPR_YOFFSET * m->res_y / spr.tf_y);
	spr.drawend_y = spr.height / 2 + m->res_y / 2 +
		(int)(SPR_YOFFSET * m->res_y / spr.tf_y);
	if (spr.drawstart_y < 0)
		spr.drawstart_y = 0;
	if (spr.drawend_y > m->res_y)
		spr.drawend_y = m->res_y;
	spr.width = abs((int)(m->res_y / spr.tf_y)) / SPR_SCALE_DIV;
	spr.drawstart_x = -spr.width / 2 + spr.scr_x;
	spr.drawend_x = spr.width / 2 + spr.scr_x;
	if (spr.drawstart_x < 0)
		spr.drawstart_x = 0;
	if (spr.drawend_x > m->res_x)
		spr.drawend_x = m->res_x;
	return (spr);
}

static void		ft_drawspriteline(t_mlx *m, t_spr spr, int x, int **out)
{
	int		y;
	int		tex_x;
	int		tex_y;
	int		argb;

	tex_x = (x - (-spr.width / 2 + spr.scr_x)) * m->tex[4].width / spr.width;
	if (spr.tf_y < m->cam->zdist[x])
	{
		y = spr.drawstart_y - 1;
		while (++y < spr.drawend_y)
		{
			tex_y = ((((y - (int)(SPR_YOFFSET * m->res_y / spr.tf_y)) * 256 -
				m->res_y * 128 + spr.height * 128) * m->tex[4].height) /
				spr.height) / 256;
			argb = m->tex[4].addr[tex_y * m->tex[4].width + tex_x];
			if ((argb & 0x00FFFFFF) != 0)
				(*out)[y * m->res_x + x] = argb;
		}
	}
}

void			ft_spritecast(t_mlx *m, t_cam *c, int **out)
{
	int		s;
	int		x;

	ft_sortsprites(m->spr, c->spr);
	s = -1;
	while (++s < c->spr)
	{
		m->spr[s] = ft_definespr(m->spr[s], c, m);
		x = m->spr[s].drawstart_x - 1;
		while (++x < m->spr[s].drawend_x)
			ft_drawspriteline(m, m->spr[s], x, out);
	}
}
