NAME = Cub

CC = cc

mlx_lib = minilibx_opengl_20191021/libmlx.a

CFLAGS = -Wall -Wextra -Werror -g
	
OBJS = 	main.o \
		parse.o\
		get_next_line.o \
		get_next_line_util.o\
		function_util.o\
		ft_split.o\
		ft_split_utils.o\
		drow_map.o\
		function_utils_2.o\
		check_2.o\
		check.o\

RM = rm -f 
 
all : $(NAME)

$(NAME): $(OBJS) $(mlx_lib)
	$(CC) $(OBJS) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c cub.h mlx.h mlx_png.h mlx_opengl.h mlx_int.h 
	$(CC) $(CFLAGS) -c $< -o $@

$(mlx_lib): minilibx_opengl_20191021/mlx.h
	$(MAKE) -C minilibx_opengl_20191021

clean:
	$(RM) $(OBJS) 
	$(MAKE) -C minilibx_opengl_20191021 clean

fclean: clean
	$(RM) $(NAME) $(mlx_lib)

re: fclean all 