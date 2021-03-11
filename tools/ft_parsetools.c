#include "cub3d.h"

void		ft_getresolution(t_mlx *m, char *s)
{
	if (m->res_x != -1 || m->res_y != -1)
		ft_error(m, 9, m->cfg->line);
	if (!ft_isspace(*s) && *s != '\0')
		ft_error(m, 2, m->cfg->line);
	while (ft_isspace(*s))
		s++;
	if (!ft_isdigit(*s) || ft_strnumlen(s) > 9)
		ft_error(m, 5, m->cfg->line);
	m->res_x = ft_atoi(s);
	while (ft_isdigit(*s))
		s++;
	while (ft_isspace(*s))
		s++;
	if (!ft_isdigit(*s) || ft_strnumlen(s) > 9)
		ft_error(m, 5, m->cfg->line);
	m->res_y = ft_atoi(s);
	while (ft_isdigit(*s))
		s++;
	if (*s != '\0')
		ft_error(m, 5, m->cfg->line);
	if (m->res_x < 1 || m->res_y < 1)
		ft_error(m, 5, m->cfg->line);
}

static int	ft_numcount(char *s)
{
	int		i;

	i = 0;
	while (*s != '\0')
	{
		while (ft_isspace(*s))
			s++;
		if (ft_isdigit(*s))
			i++;
		while (ft_isdigit(*s))
			s++;
		if (*s != ',' && *s != '\0')
			return (-1);
		if (*s == ',')
			s++;
	}
	return (i);
}

static int	ft_commacount(char *s)
{
	int		i;

	i = 0;
	while (*s != '\0')
	{
		if (*s == ',')
			i++;
		s++;
	}
	return (i);
}

void		ft_getargb(t_mlx *m, char *s, int *argb)
{
	int		digit;
	int		rgb[3];

	digit = 0;
	if (*argb != -1)
		ft_error(m, 9, m->cfg->line);
	if (!ft_isspace(*s) && *s != '\0')
		ft_error(m, 2, m->cfg->line);
	if (ft_numcount(s) != 3 || ft_commacount(s) != 2)
		ft_error(m, 6, m->cfg->line);
	while (*s != '\0' && digit < 3)
	{
		while (ft_isspace(*s))
			s++;
		if (ft_isdigit(*s) && ft_atoi(s) >= 0 && ft_atoi(s) < 256)
			rgb[digit] = ft_atoi(s);
		else
			ft_error(m, 6, m->cfg->line);
		while (ft_isdigit(*s))
			s++;
		if (*s == ',')
			s++;
		digit++;
	}
	*argb = ft_toargb(0, rgb[0], rgb[1], rgb[2]);
}

void		ft_getpath(t_mlx *m, char *s, char **path)
{
	int		fd;

	if (*path != NULL)
		ft_error(m, 9, m->cfg->line);
	if (!ft_isspace(*s) && *s != '\0')
		ft_error(m, 2, m->cfg->line);
	while (ft_isspace(*s))
		s++;
	if (*s == '\0')
		ft_error(m, 7, m->cfg->line);
	if (ft_strncmp(s + ft_strlen(s) - 4, ".xpm", 5) != 0)
		ft_error(m, 14, s);
	if ((fd = open(s, O_RDONLY)) < 0)
		ft_error(m, -1, s);
	*path = ft_strdup(s);
	if (*path == NULL)
		ft_error(m, -1, "Config paths parse");
	close(fd);
}
