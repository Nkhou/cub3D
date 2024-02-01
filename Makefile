NAME = cub3D
NAME_BONUS = cub3D_bonus

CC = cc

mlx_lib = MLX42/build/libmlx42.a 

CFLAGS = -Wall -Wextra -Werror -Ofast

F_MLX = -framework Cocoa -framework OpenGL -framework IOKit -lglfw
MLX_H =  MLX42/include/MLX42/MLX42.h

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
		mandatory/parse/_norm_ceil_floor.o\
		mandatory/parse/ft_space_.o\
		mandatory/parse/norm_position.o\
		mandatory/Utils/get_next_line.o \
		mandatory/Utils/get_next_line_util.o\
		mandatory/Utils/function_util.o\
		mandatory/Utils/ft_split.o\
		mandatory/Utils/ft_split_utils.o\
		mandatory/Utils/function_utils_2.o\
		mandatory/Utils/utils_3.o\
		mandatory/Utils/ft_get_rgb.o\
		mandatory/Utils/util_norm.o\
		mandatory/Utils/other_func.o\
		mandatory/Utils/other_2.o\
		mandatory/Utils/util_lines.o\
		mandatory/game3D/drow_map.o\
		mandatory/game3D/get_textures.o\
		mandatory/game3D/game_draw.o\
		mandatory/game3D/build_map.o\
		mandatory/game3D/cast_ray.o\
		mandatory/game3D/direction.o\
		mandatory/game3D/key.o\
		mandatory/game3D/Drawing.o\

BONUS = bonus/cub3d.o \
		bonus/parse/parse.o\
		bonus/parse/check_utils.o\
		bonus/parse/ft_position.o\
		bonus/parse/check_2.o\
		bonus/parse/check.o\
		bonus/parse/norm.o \
		bonus/parse/norm_2.o\
		bonus/parse/norm_position.o\
		bonus/parse/_norm_ceil_floor.o\
		bonus/parse/ft_space_.o\
		bonus/Utils/get_next_line.o \
		bonus/Utils/get_next_line_util.o\
		bonus/Utils/function_util.o\
		bonus/Utils/ft_split.o\
		bonus/Utils/ft_split_utils.o\
		bonus/Utils/function_utils_2.o\
		bonus/Utils/utils_3.o\
		bonus/Utils/ft_get_rgb.o\
		bonus/Utils/util_norm.o\
		bonus/Utils/other_func.o\
		bonus/Utils/other_2.o\
		bonus/Utils/util_lines.o\
		bonus/game3D/drow_map_bonus.o\
		bonus/game3D/get_textures_bonus.o\
		bonus/game3D/game_draw_bonus.o\
		bonus/game3D/build_map_bonus.o\
		bonus/game3D/cast_ray_bonus.o\
		bonus/game3D/direction_bonus.o\
		bonus/game3D/key_bonus.o\
		bonus/game3D/minimap_bonus.o\
		bonus/game3D/check_wall_bonus.o\
		bonus/game3D/Drawing_bonus.o\

RM = rm -f 
 
all : $(NAME)

bonus : $(NAME_BONUS)

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $(F_MLX) $(OBJS) libmlx42.a   $(LIB_GLFW) $(GLFW) -o $(NAME)

$(NAME_BONUS): $(BONUS) $(NAME)
	$(CC) $(CFLAGS) $(F_MLX) $(BONUS) libmlx42.a   $(LIB_GLFW) $(GLFW) -o $(NAME_BONUS)

%.o: %.c include/cub.h
	$(CC) $(CFLAGS) $(GLFW) -c $< -o $@

clean:
	$(RM) $(OBJS)  $(BONUS)

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)

re: fclean all 
