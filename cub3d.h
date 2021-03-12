#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <math.h>
# include <string.h>
# include <sys/errno.h>
# include "libft/libft.h"
# include "libft/get_next_line.h"
# include "minilibx/mlx.h"

# ifndef M_PI
#  define M_PI			3.14159265358979323846
# endif

# define FOV			77.0
# define SPR_SCALE_DIV	2
# define SPR_YOFFSET	0.34
# define MSPD			0.3
# define RSPD			0.12

# define KEY_W			119
# define KEY_A			97
# define KEY_S			115
# define KEY_D			100
# define KEY_LEFT		65361
# define KEY_RIGHT		65363
# define KEY_ESC		65307

# define SCREENSHOT_DPI 72

typedef struct		s_spr
{
	double			x;
	double			y;
	double			dist;
	double			tf_x;
	double			tf_y;
	int				scr_x;
	int				height;
	int				width;
	int				drawstart_x;
	int				drawend_x;
	int				drawstart_y;
	int				drawend_y;
}					t_spr;

typedef struct		s_ray
{
	double			cam_x;
	double			deltadist_x;
	double			deltadist_y;
	double			sidedist_x;
	double			sidedist_y;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
}					t_ray;

typedef struct		s_wall
{
	double			wall_x;
	int				tex_x;
	int				tex_y;
	double			tex_step;
	double			tex_pos;
	int				line_height;
	int				drawstart;
	int				drawend;
}					t_wall;

typedef struct		s_cam
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			raydir_x;
	double			raydir_y;
	double			*zdist;
	int				side;
	int				spr;
}					t_cam;

typedef struct		s_cfg
{
	int				fd;
	char			*line;
	int				bmp;
	char			*tpath[5];
	int				f_argb;
	int				c_argb;
	char			*mapline;
	char			**map;
	int				map_w;
	int				map_h;
	int				start_x;
	int				start_y;
	char			start_dir;
	int				spr_num;
}					t_cfg;

typedef struct		s_img
{
	void			*img;
	int				*addr;
	int				bpp;
	int				size_line;
	int				endian;
	int				width;
	int				height;
}					t_img;

typedef struct		s_mlx
{
	void			*mlx;
	void			*wnd;
	int				res_x;
	int				res_y;
	t_cfg			*cfg;
	t_img			frame;
	t_img			tex[5];
	t_cam			*cam;
	t_spr			*spr;
	unsigned char	*bytes;
	int				exitcode;
}					t_mlx;

int					ft_exit(t_mlx *m);
void				ft_error(t_mlx *m, int errnum, char *filename);

void				ft_initbase(t_mlx *m);
void				ft_getresolution(t_mlx *m, char *s);
void				ft_getargb(t_mlx *m, char *s, int *argb);
void				ft_getpath(t_mlx *m, char *s, char **path);
int					ft_ismapstr(char *s);
void				ft_checkmap(t_mlx *m);
void				ft_parsemap(t_mlx *m, t_cfg *c);
void				ft_parsecfg(t_mlx *m, t_cfg *c);

void				ft_fitresolution(t_mlx *m);
void				ft_initcam(t_mlx *m);
void				ft_loadtextures(t_mlx *m);

void				ft_bmp(t_mlx *m);
int					ft_control(int key, t_mlx *m);
void				ft_window(t_mlx *m);
void				ft_render(t_mlx *m);

void				ft_countsprites(t_cfg *c, char **map);
void				ft_addsprite(t_mlx *m, t_cam *c, t_ray r);
void				ft_sortsprites(t_spr *s, int count);

void				ft_raycast(t_mlx *m, t_cam *c, int i);
void				ft_wallcast(t_mlx *m, t_cam *c, int **out);
void				ft_spritecast(t_mlx *m, t_cam *c, int **out);

#endif
