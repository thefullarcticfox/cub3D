#include "cub3d.h"

static void		ft_getstartpos(t_mlx *m)
{
	int		x;
	int		y;

	x = -1;
	while (++x < m->cfg->map_h)
	{
		y = -1;
		while (++y < m->cfg->map_w)
		{
			if (m->cfg->map[x][y] == 'N' || m->cfg->map[x][y] == 'E' ||
				m->cfg->map[x][y] == 'S' || m->cfg->map[x][y] == 'W')
			{
				if (m->cfg->start_x == -1 && m->cfg->start_y == -1)
				{
					m->cfg->start_x = x;
					m->cfg->start_y = y;
					m->cfg->start_dir = m->cfg->map[x][y];
				}
				else
					ft_error(m, 11, NULL);
			}
		}
	}
	if (m->cfg->start_x == -1 && m->cfg->start_y == -1)
		ft_error(m, 12, NULL);
}

static void		ft_isclosedmaphor(t_mlx *m)
{
	int		x;
	int		y;

	x = -1;
	while (++x < m->cfg->map_h)
	{
		y = -1;
		while (++y < m->cfg->map_w)
		{
			if (m->cfg->map[x][y] == ' ')
				continue ;
			if (m->cfg->map[x][y] != '1')
				ft_error(m, 4, NULL);
			else
			{
				while (++y < m->cfg->map_w && m->cfg->map[x][y] != ' ')
					;
				if (m->cfg->map[x][y - 1] != '1')
					ft_error(m, 4, NULL);
			}
		}
	}
}

static void		ft_isclosedmapver(t_mlx *m)
{
	int		x;
	int		y;

	y = -1;
	while (++y < m->cfg->map_w)
	{
		x = -1;
		while (++x < m->cfg->map_h)
		{
			if (m->cfg->map[x][y] == ' ')
				continue ;
			if (m->cfg->map[x][y] != '1')
				ft_error(m, 4, NULL);
			else
			{
				while (++x < m->cfg->map_h && m->cfg->map[x][y] != ' ')
					;
				if (m->cfg->map[x - 1][y] != '1')
					ft_error(m, 4, NULL);
			}
		}
	}
}

static void		ft_alignmap(t_mlx *m, t_cfg *c)
{
	int		i;
	int		j;

	i = 0;
	while (c->map[i] != NULL)
	{
		if ((int)ft_strlen(c->map[i]) < c->map_w)
		{
			c->mapline = (char *)malloc(sizeof(char) * (c->map_w + 1));
			if (c->mapline == NULL)
				ft_error(m, -1, "Map alignment");
			ft_memset(c->mapline, ' ', c->map_w);
			c->mapline[c->map_w] = '\0';
			j = -1;
			while (c->map[i][++j] != '\0')
				c->mapline[j] = c->map[i][j];
			free(c->map[i]);
			c->map[i] = c->mapline;
		}
		i++;
	}
	c->mapline = NULL;
}

void			ft_checkmap(t_mlx *m)
{
	if (m->cfg->map_h < 3 || m->cfg->map_w < 3)
		ft_error(m, 3, NULL);
	ft_alignmap(m, m->cfg);
	ft_getstartpos(m);
	ft_isclosedmaphor(m);
	ft_isclosedmapver(m);
}
