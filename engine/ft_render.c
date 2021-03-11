#include "cub3d.h"

void		ft_render(t_mlx *m)
{
	int		i;

	m->frame.img = mlx_new_image(m->mlx, m->res_x, m->res_y);
	if (m->frame.img == NULL)
		ft_error(m, 19, "Frame render");
	m->frame.addr = (int *)mlx_get_data_addr(m->frame.img,
		&m->frame.bpp, &m->frame.size_line, &m->frame.endian);
	if (m->frame.addr == NULL)
		ft_error(m, 20, "Frame render");
	i = -1;
	while (++i < m->res_x * (m->res_y / 2))
		m->frame.addr[i] = m->cfg->c_argb;
	while (++i < m->res_x * m->res_y)
		m->frame.addr[i] = m->cfg->f_argb;
	m->cam->spr = 0;
	ft_wallcast(m, m->cam, &(m->frame.addr));
	ft_spritecast(m, m->cam, &(m->frame.addr));
}
