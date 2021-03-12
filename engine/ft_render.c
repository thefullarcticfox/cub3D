#include "cub3d.h"

void		ft_render(t_mlx *m)
{
	int		i;

	i = -1;
	while (++i < m->res_x * (m->res_y / 2))
		m->frame.addr[i] = m->cfg->c_argb;
	while (++i < m->res_x * m->res_y)
		m->frame.addr[i] = m->cfg->f_argb;
	m->cam->spr = 0;
	ft_wallcast(m, m->cam, &(m->frame.addr));
	ft_spritecast(m, m->cam, &(m->frame.addr));
}
