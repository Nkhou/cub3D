NAME = Cub

CC = cc

mlx_lib = MLX42/build/libmlx42.a 

CFLAGS = -Wall -Wextra -Werror  -g #-fsanitize=address

F_MLX = -framework Cocoa -framework OpenGL -framework IOKit -lglfw
MLX_H =  MLX42/include/MLX42/MLX42.h
#BUILD = MLX42/build

GLFW = -I/Users/$(USER)/.brew/Cellar/glfw/3.3.9/include/GLFW
LIB_GLFW = -L/Users/$(USER)/.brew/Cellar/glfw/3.3.9/lib

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
		get_textures.o\
		check_utils.o\

RM = rm -f 
 
all : $(NAME)

# $(NAME): $(OBJS) $(mlx_lib) $(BUILD)
$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $(F_MLX) $(OBJS) MLX42/build/libmlx42.a   $(LIB_GLFW) $(GLFW) -o $(NAME)
# MLX42/include/KHR/khrplatform.h MLX42/include/lodepng/lodepng.h MLX42/include/MLX42/MLX42_Int.h MLX42/include/MLX42/MLX42.h  MLX42/glad/glad.h
%.o: %.c cub.h
	$(CC) $(CFLAGS) $(GLFW) -c $< -o $@

# $(mlx_lib): MLX42/include/KHR/khrplatform.h MLX42/include/lodepng/lodepng.h MLX42/include/MLX42/MLX42_Int.h MLX42/include/MLX42/MLX42.h MLX42/glad/glad.h
# 	$(MAKE) -C MLX42

#$(BUILD):
    #@if [ ! -d MLX42/build ]; then (cd MLX42 && cmake -B build); 

clean:
	$(RM) $(OBJS) 

fclean: clean
	$(RM) $(NAME)

re: fclean all 
