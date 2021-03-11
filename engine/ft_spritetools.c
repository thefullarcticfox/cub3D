#include "cub3d.h"

void			ft_loadtextures(t_mlx *m)
{
	int		i;

	i = -1;
	while (++i < 5)
	{
		m->tex[i].img = mlx_xpm_file_to_image(m->mlx, m->cfg->tpath[i],
			&(m->tex[i].width), &(m->tex[i].height));
		if (m->tex[i].img == NULL)
			ft_error(m, 16, m->cfg->tpath[i]);
		if (m->tex[i].width < 1 || m->tex[i].height < 1)
			ft_error(m, 15, m->cfg->tpath[i]);
		m->tex[i].addr = (int *)mlx_get_data_addr(m->tex[i].img,
			&(m->tex[i].bpp), &(m->tex[i].size_line), &(m->tex[i].endian));
		if (m->tex[i].addr == NULL)
			ft_error(m, 20, "Texture load");
		free(m->cfg->tpath[i]);
		m->cfg->tpath[i] = NULL;
	}
}

void			ft_countsprites(t_cfg *cfg, char **map)
{
	int		y;
	int		x;

	cfg->spr_num = 0;
	x = -1;
	while (++x < cfg->map_h)
	{
		y = -1;
		while (++y < cfg->map_w)
		{
			if (map[x][y] == '2')
				cfg->spr_num++;
		}
	}
}

void			ft_addsprite(t_mlx *m, t_cam *c, t_ray r)
{
	int		count;

	count = c->spr;
	while (--count >= 0)
	{
		if (r.map_x == (int)floor(m->spr[count].x) &&
			r.map_y == (int)floor(m->spr[count].y))
			return ;
	}
	m->spr[c->spr].x = r.map_x + 0.5;
	m->spr[c->spr].y = r.map_y + 0.5;
	m->spr[c->spr].dist =
		((c->pos_x - m->spr[c->spr].x) * (c->pos_x - m->spr[c->spr].x)) +
		((c->pos_y - m->spr[c->spr].y) * (c->pos_y - m->spr[c->spr].y));
	c->spr++;
}

void			ft_sortsprites(t_spr *spr, int count)
{
	t_spr	temp;
	int		i;
	int		j;

	i = -1;
	while (++i < count - 1)
	{
		j = -1;
		while (++j < count - i - 1)
		{
			if (spr[j].dist < spr[j + 1].dist)
			{
				temp = spr[j];
				spr[j] = spr[j + 1];
				spr[j + 1] = temp;
			}
		}
	}
}
