NAME = cub3D
NAME_BONUS = cub3D_bonus

CC = cc

mlx_lib = MLX42/build/libmlx42.a 

CFLAGS = -Wall -Wextra -Werror  -g #-fsanitize=address

F_MLX = -framework Cocoa -framework OpenGL -framework IOKit -lglfw
MLX_H =  MLX42/include/MLX42/MLX42.h
#BUILD = MLX42/build

GLFW = -I/Users/$(USER)/.brew/Cellar/glfw/3.3.9/include/GLFW
LIB_GLFW = -L/Users/$(USER)/.brew/Cellar/glfw/3.3.9/lib

OBJS = 	mandatory/main.o \
		mandatory/parse.o\
		mandatory/get_next_line.o \
		mandatory/get_next_line_util.o\
		mandatory/function_util.o\
		mandatory/ft_split.o\
		mandatory/ft_split_utils.o\
		mandatory/drow_map.o\
		mandatory/function_utils_2.o\
		mandatory/check_2.o\
		mandatory/check.o\
		mandatory/get_textures.o\
		mandatory/check_utils.o\
		mandatory/game_draw.o\
		mandatory/build_map.o\
		mandatory/ft_position.o\
		mandatory/cast_ray.o\

BONUS = bonus/bonus_main.o \
		bonus/bonus_parse.o\
		bonus/bonus_get_next_line.o \
		bonus/bonus_get_next_line_util.o\
		bonus/bonus_function_util.o\
		bonus/bonus_ft_split.o\
		bonus/bonus_ft_split_utils.o\
		bonus/bonus_drow_map.o\
		bonus/bonus_function_utils_2.o\
		bonus/bonus_check_2.o\
		bonus/bonus_check.o\
		bonus/bonus_get_textures.o\
		bonus/bonus_check_utils.o\
		bonus/bonus_game_draw.o\
		bonus/bonus_build_map.o\
		bonus/bonus_ft_position.o\
		bonus/bonus_cast_ray.o\

RM = rm -f 
 
all : $(NAME)

bonus : $(NAME_BONUS)
# $(NAME): $(OBJS) $(mlx_lib) $(BUILD)
$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $(F_MLX) $(OBJS) MLX42/build/libmlx42.a   $(LIB_GLFW) $(GLFW) -o $(NAME)

$(NAME_BONUS): $(BONUS)
	$(CC) $(CFLAGS) $(F_MLX) $(BONUS) MLX42/build/libmlx42.a   $(LIB_GLFW) $(GLFW) -o $(NAME_BONUS)
# MLX42/include/KHR/khrplatform.h MLX42/include/lodepng/lodepng.h MLX42/include/MLX42/MLX42_Int.h MLX42/include/MLX42/MLX42.h  MLX42/glad/glad.h
%.o: %.c /include/cub.h
	$(CC) $(CFLAGS) $(GLFW) -c $< -o $@

%.o: %.c /include/cub.h
	$(CC) $(CFLAGS) $(GLFW) -c $< -o $@
# $(mlx_lib): MLX42/include/KHR/khrplatform.h MLX42/include/lodepng/lodepng.h MLX42/include/MLX42/MLX42_Int.h MLX42/include/MLX42/MLX42.h MLX42/glad/glad.h
# 	$(MAKE) -C MLX42

#$(BUILD):
    #@if [ ! -d MLX42/build ]; then (cd MLX42 && cmake -B build); 

clean:
	$(RM) $(OBJS)  $(BONUS)

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)

re: fclean all 
