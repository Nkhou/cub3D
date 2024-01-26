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

OBJS = 	mandatory/cub3d.o \
		mandatory/parse/parse.o\
		mandatory/parse/check_utils.o\
		mandatory/parse/ft_position.o\
		mandatory/parse/check_2.o\
		mandatory/parse/check.o\
		mandatory/parse/norm.o \
		mandatory/parse/norm_2.o\
		mandatory/parse/ft_space_.o\
		mandatory/Utils/get_next_line.o \
		mandatory/Utils/get_next_line_util.o\
		mandatory/Utils/function_util.o\
		mandatory/Utils/ft_split.o\
		mandatory/Utils/ft_split_utils.o\
		mandatory/Utils/function_utils_2.o\
		mandatory/game3D/drow_map.o\
		mandatory/game3D/get_textures.o\
		mandatory/game3D/game_draw.o\
		mandatory/game3D/build_map.o\
		mandatory/game3D/cast_ray.o\

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
