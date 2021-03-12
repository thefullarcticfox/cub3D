NAME = cub3D

SRC = tools/ft_initbase.c tools/ft_exit.c tools/ft_error.c \
	tools/ft_parsetools.c tools/ft_parsecfg.c \
	tools/ft_parsemap.c tools/ft_checkmap.c \
	engine/ft_initcam.c engine/ft_render.c \
	engine/ft_raycast.c engine/ft_wallcast.c \
	engine/ft_spritetools.c engine/ft_spritecast.c \
	engine/ft_control.c engine/ft_window.c engine/ft_bmp.c \
	cub3d.c

OBJ = $(SRC:.c=.o)
INCLUDEDIR = ./
HEADERS = $(INCLUDEDIR)cub3d.h
LIBFTDIR = ./libft/
LIBFT = $(LIBFTDIR)libft.a
MINILIBXDIR = ./minilibx/
MINILIBX = $(MINILIBXDIR)libmlx.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(INCLUDEDIR)
LIBFLAGS = -lm -L$(LIBFTDIR) -lft -L$(MINILIBXDIR) -lmlx
FRAMEWORKS = -lXext -lX11 -lm -lbsd
EXECFLAGS = $(CFLAGS) $(LIBFLAGS) $(FRAMEWORKS)

.PHONY: all bonus clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(EXECFLAGS)

%.o: %.c $(HEADERS) $(LIBFT) $(MINILIBX)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@echo "> Building libft"
	@make -C $(LIBFTDIR)
	@echo "> Done\n"

$(MINILIBX):
	@echo "> Building minilibx"
	@make -C $(MINILIBXDIR)
	@echo "> Done\n"

clean:
	@make clean -C $(LIBFTDIR)
	@make clean -C $(MINILIBXDIR)
	@/bin/rm -f $(OBJ)

fclean: clean
	@make fclean -C $(LIBFTDIR)
	@/bin/rm -f $(NAME)

re: fclean all
