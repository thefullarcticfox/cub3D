#include "cub3d.h"

static int	ft_processline(t_mlx *m, t_cfg *c)
{
	if (ft_strncmp(c->line, "R", 1) == 0)
		ft_getresolution(m, c->line + 1);
	else if (ft_strncmp(c->line, "NO", 2) == 0)
		ft_getpath(m, c->line + 2, &(c->tpath[0]));
	else if (ft_strncmp(c->line, "WE", 2) == 0)
		ft_getpath(m, c->line + 2, &(c->tpath[1]));
	else if (ft_strncmp(c->line, "EA", 2) == 0)
		ft_getpath(m, c->line + 2, &(c->tpath[2]));
	else if (ft_strncmp(c->line, "SO", 2) == 0)
		ft_getpath(m, c->line + 2, &(c->tpath[3]));
	else if (ft_strncmp(c->line, "S", 1) == 0)
		ft_getpath(m, c->line + 1, &(c->tpath[4]));
	else if (ft_strncmp(c->line, "F", 1) == 0)
		ft_getargb(m, c->line + 1, &(c->f_argb));
	else if (ft_strncmp(c->line, "C", 1) == 0)
		ft_getargb(m, c->line + 1, &(c->c_argb));
	else if (ft_ismapstr(c->line) && !ft_isalpha(c->line[0]))
	{
		ft_parsemap(m, c);
		return (0);
	}
	else if (ft_strlen(c->line) > 0)
		return (-1);
	return (1);
}

void		ft_parsecfg(t_mlx *m, t_cfg *c)
{
	int			result;
	int			gnlresult;

	while ((gnlresult = get_next_line(m->cfg->fd, &(c->line))) >= 0)
	{
		result = ft_processline(m, c);
		if (gnlresult == 0 || result == 0)
		{
			close(c->fd);
			break ;
		}
		if (result == -1)
			ft_error(m, 2, c->line);
		free(c->line);
		c->line = NULL;
	}
	if (gnlresult < 0)
		ft_error(m, -1, "Config parse (get_next_line)");
	if (c->map == NULL)
		ft_error(m, 21, NULL);
}
