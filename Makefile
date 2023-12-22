NAME = Cub

CC = cc
 
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

$(NAME): $(OBJS)
	$(CC) $(OBJS) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c cub.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) 

fclean: clean
	$(RM) $(NAME)

re: fclean all 