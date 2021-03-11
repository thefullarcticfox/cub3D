#include "cub3d.h"

void		ft_fitresolution(t_mlx *m)
{
	int		scr_x;
	int		scr_y;

	mlx_get_screen_size(m->mlx, &scr_x, &scr_y);
	if (m->res_x > scr_x)
		m->res_x = scr_x;
	if (m->res_y > scr_y)
		m->res_y = scr_y;
}

void		ft_window(t_mlx *m)
{
	m->wnd = mlx_new_window(m->mlx, m->res_x, m->res_y, "cub3D");
	if (m->wnd == NULL)
		ft_error(m, 18, "Window open");
	ft_putstr_fd("Window opened\n", 1);
	ft_render(m);
	mlx_put_image_to_window(m->mlx, m->wnd, m->frame.img, 0, 0);
	mlx_destroy_image(m->mlx, m->frame.img);
	m->frame.img = NULL;
	mlx_hook(m->wnd, 2, 1L << 0, ft_control, m);
	mlx_hook(m->wnd, 17, 1L << 17, ft_exit, m);
	mlx_loop(m->mlx);
}
