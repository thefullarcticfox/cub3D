#include "cub3d.h"

static int		ft_isgoodcfg(t_mlx *m)
{
	if (m->res_x == -1 || m->res_y == -1 ||
		m->cfg->tpath[0] == NULL || m->cfg->tpath[1] == NULL ||
		m->cfg->tpath[2] == NULL || m->cfg->tpath[3] == NULL ||
		m->cfg->tpath[4] == NULL || m->cfg->f_argb == -1 ||
		m->cfg->c_argb == -1)
		return (0);
	return (1);
}

int				ft_ismapstr(char *s)
{
	size_t	len;
	size_t	spaces;

	len = ft_strlen(s);
	if (len == 0)
		return (0);
	spaces = 0;
	while (*s != '\0')
	{
		if (!(*s == '0' || *s == '1' || *s == '2' || *s == ' ' ||
			*s == 'N' || *s == 'E' || *s == 'W' || *s == 'S'))
			return (0);
		if (*s == ' ')
			spaces++;
		s++;
	}
	if (spaces == len)
		return (0);
	return (1);
}

static void		ft_add_to_mapline(t_mlx *m, t_cfg *c)
{
	char	*tmp;

	if (!ft_ismapstr(c->line))
		ft_error(m, 8, c->line);
	if ((int)ft_strlen(c->line) > c->map_w)
		c->map_w = (int)ft_strlen(c->line);
	tmp = c->mapline;
	c->mapline = ft_strjoin(c->mapline, c->line);
	free(tmp);
	free(c->line);
	c->line = NULL;
	if (c->mapline == NULL)
		ft_error(m, -1, "Map parse");
	tmp = c->mapline;
	c->mapline = ft_strjoin(c->mapline, "\n");
	free(tmp);
	if (c->mapline == NULL)
		ft_error(m, -1, "Map parse");
	c->map_h++;
}

static void		ft_readmap(t_mlx *m, t_cfg *c)
{
	int		gnlresult;
	char	*tmp;

	tmp = c->line;
	c->mapline = ft_strjoin(c->line, "\n");
	free(tmp);
	c->line = NULL;
	if (c->mapline == NULL)
		ft_error(m, -1, "Map parse");
	while ((gnlresult = get_next_line(c->fd, &(c->line))) >= 0)
	{
		if (gnlresult > 0 || ft_strlen(c->line) > 0)
			ft_add_to_mapline(m, c);
		else
			break ;
	}
	free(c->line);
	c->line = NULL;
	if (gnlresult < 0)
		ft_error(m, -1, "Map parse (get_next_line)");
}

void			ft_parsemap(t_mlx *m, t_cfg *c)
{
	if (!ft_isgoodcfg(m))
		ft_error(m, 10, NULL);
	c->map_w = ft_strlen(c->line);
	c->map_h = 1;
	ft_readmap(m, c);
	if (!(c->map = ft_split(c->mapline, '\n')))
		ft_error(m, -1, "Map parse (ft_split)");
	free(c->mapline);
	c->mapline = NULL;
	ft_checkmap(m);
}
