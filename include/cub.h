/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 13:23:54 by saboulal          #+#    #+#             */
/*   Updated: 2024/01/30 20:53:29 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include <limits.h>
# include "../MLX42.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42

# endif

# define NB_RAYS 1900
# define TILE_SIZE 64
# define WIDTH 1900
# define HEIGHT 1200
# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3
# define DOOR 4

typedef struct s_hv
{
	double	wallhitx;
	double	wallhity;
	double	distance;
	int		content;
	int		fhwh;
	int		fhwv;
}	t_hv;
typedef struct s_tex
{
	int		no;
	int		so;
	int		we;
	int		ea;
	int		f;
	int		c;
}	t_tex;

typedef struct s_step
{
	double	xstep;
	double	ystep;
}	t_step;

typedef struct direction
{
	int	up;
	int	down;
	int	left;
	int	right;
}	t_direction;

typedef struct horz
{
	double	xintercept;
	double	yintercept;
	double	xstep;
	double	ystep;
	double	nextx;
	double	nexty;
	double	xtocheck;
	double	ytocheck;
	double	horzwallhitx;
	double	horzwallhity;
	int		foundhorzwallhit;
}	t_horz;

typedef struct min
{
	double	x;
	double	y;
	int		i;
	int		j;
}	t_min;

typedef struct ray
{
	double	raya;
	double	wallhy;
	double	wallhx;
	double	distance;
	int		isv;
	int		ish;
	int		isu;
	int		isd;
	int		isl;
	int		isr;
	int		content;
}	t_ray;

typedef struct s_player
{
	t_ray	*rays;
	double	x;
	double	y;
	double	width;
	double	height;
	double	pa;
	double	pdx;
	double	pdy;
	int		d;
	int		td;
	int		wd;
	int		wlr;
	double	ra;
	double	ws;
	double	ts;
	int		direction;
	double	delta;
}	t_player;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_map
{
	int				prev;
	char			dr;
	t_player		player;
	char			**map;
	double			fav;
	char			**map1;
	char			*str;
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	t_rgb			*ceil;
	t_rgb			*floor;
	int				width;
	int				height;
	int				size;
	int				len;
	int				start;
	int				r;
	int				c;
	void			*mlx;
	char			**tab;
	mlx_image_t		*img;
	mlx_texture_t	**texture;
}	t_map;

typedef struct projection
{
	double	wallstripheight;
	double	distanceprojplane;
	double	projwallheight;
	double	perpdistance;
	int		walltoppixel;
	int		wallbottompixel;
}	t_projection;

char	*ft_strjoin(char *left_str, char *buff);
char	*ft_strdup(char *str);
char	*ft_read(int fd, char *str);
char	*ft_get_line(char **str);
char	*ft_next_right(char *str);
char	*get_next_line(int fd);
char	**ft_split(char const *s, char c);
char	*ft_strdup_1(char *str);
char	*ft_substr(char *s, unsigned int start, size_t len);
size_t	ft_strlcpy(char *dest, char *src, size_t size);
void	ft_free(char **p);
int		ft_strncmp(const char *f, const char *s, int len);
int		ft_strlen(char *str);
int		ft_strchr(char *str);
int		check_exet(char *str, char *exe);
int		ft_isalpha(int c);
int		ft_atoi(const char *str);
char	*ft_strchr_1(const char *s, int c);
char	*ft_strndup(char *s1, int n);
int		check_new_line(char *str);
int		ft_at(const char *str, int sgn);
void	ft_rgb_cor1(char **p, t_map *map);
int		check_nub_line(char *path);
int		len_map(char **map);
void	ini_map(t_map *map, int argc);
int		check_player_surroundings(char **map, int r, int c);
void	init_infos(t_map *map, char **argv);
void	ft_extention(char **argv);
char	*check_before_map(char *path);
void	init_part_map(t_map *map);
void	init_parse(t_map *map);
void	get_space_wall(t_map map);
int		cmp_line(char **str);
int		check_nbr_char(char **map);
int		check_nbr_height(char **map);
int		check_white_space(t_map *map);
void	check_texture_map(t_map *map);
void	ft_error_wall(void);
void	map_game_full(t_map map);
void	map_checks_(t_map map, int r, int c);
void	map_game(char **map);
int		space_waall(char **map, int r, int c);
int		found_wall(char **map, int r);
void	get_map(t_map *map);
void	ft_error(void);
void	free_programme(t_map *map);
void	for_leak_mlx(t_map *map);
void	moveplayer(t_map *map);
int		map_wall(double x, double y, t_map *map);
char	*ft_strtrim(char *s1, char *set);
int		check_path(t_map *map);
int		rgb_to_int(int r, int g, int b, int a);
int		ft_north(t_map *map, int i, int k);
int		ft_south(t_map *map, int i, int k);
int		ft_west(t_map *map, int i, int k);
int		ft_east(t_map *map, int i, int k);
int		floor_(t_map *map);
int		ceilling_(t_map *map);
int		draw_3d_line(t_map *map, int i);
int		pixels_color_rgb(mlx_texture_t *p, u_int32_t x, u_int32_t y);
void	generate_3d_projection(t_map *map);
void	ft_rgb_cor(char **p, t_map *map);
void	draw_c_f(t_map *map, int i);
void	pp(t_map *map, int i, t_projection p);
void	check_rgb_ceil(t_map *map);
void	check_rgb_floor(t_map *map);
void	castrays(t_map *map);
void	map_draw(t_map map);
int		distance_between_points(double x1, double y1, double x2, double y2);
int		israyfacingdown(double rayangle);
int		israyfacingup(double rayangle);
int		israyfacingright(double rayangle);
int		israyfacingleft(double rayangle);
double	fix_angle(double angle);
t_hv	vert_(t_map *map, double ra, t_direction direction);
t_hv	incrver(t_horz v, t_map *map, t_direction direction, double ra);
t_hv	stor_vert_ray(t_map *map, t_hv vert, t_horz v, t_direction direction);
t_hv	horz_(t_map *map, double ra, t_direction direction);
t_hv	stor_ray(t_map *map, t_hv horz, t_horz h, t_direction direction);
void	comm_distance(t_map *map, int i, t_hv horz, t_hv vert);
void	castr(t_map *map, double ra, int i);
void	intial_mlx(t_map *map);
void	key_press(mlx_key_data_t keydata, void *mlx);
void	initial_data(t_map *map);
void	inttocheck(t_horz *h, t_direction direction, int i);
t_hv	stor_ray(t_map *map, t_hv horz, t_horz h, t_direction direction);
void	find_player(t_map *map);
void	draw_player(t_map *map);
void	draw_minmap(t_map *map, t_min *min);
void	minimap(t_map *map);
int		cmp_comma(char *str);
int		ft_strchr2(char *str, char c);
void	init_tex(t_tex tex);
void	stor_to_map(t_map map);
int		check_map(char **map);
void	check_pos_line_f(char *str, int i, t_tex *tex);
void	count_line_str(char *str, int i);
void	_norm_1(char *str, int i);
void	_norm(char *str, int i, t_tex *tex);
void	check_line_a(char *str, t_tex *tex, t_map *map);
void	check_line_str(char *str, int i, t_map *map);
void	init_part_map(t_map *map);
void	check_pos_line_no(char *str, int i, t_tex *tex);
void	check_pos_line_so(char *str, int i, t_tex *tex);
void	check_pos_line_we(char *str, int i, t_tex *tex);
void	check_pos_line_ea(char *str, int i, t_tex *tex);
void	check_wesfc(t_tex *tex);
void	check_retour(char *str, int i);
void	init_vaar(t_tex *tex);
char		*ft_skip_1(char *map, char *p);
int	ft_isdigit(char c);
void	check(char *str);

#endif