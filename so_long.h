#ifndef SO_LONG_H
#define SO_LONG_H

#include <stdio.h>


#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <mlx.h>

typedef struct s_info
{
	int row_len;
	int	n_column;
	int n_collec;
}	t_info;

typedef struct s_pos
{
	int 	r;
	int 	c;
}				t_pos; 

typedef struct s_donne
{
	struct s_pos 	player;
	struct s_info 	data;
	char 		**map;
	void 		*mlx;
	void 		*win;
} 				t_donne;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

int		ft_strlen(char *str, char set);
int		check_param(char *parm);
int 	key_hook(int keycode, t_donne *vars);
char	*try2read_map(char *name_file);
char	*ft_strjoin(char *s1, char *s2, int len);
char	**ft_split(char *str, t_info *data);
void	first_map_check(char *str, t_info *data);
void	second_map_check(char **map, t_info data);
void	check_a_solution(char **map, t_info data, int x, int y);
void	err_msg(char *str);
void	last_check(char **map, t_pos E);
void	get_position(char **map, char target, t_pos *position);
void	ft_clean(char **map);
void 	rendering_imgs(char *filename, void *mlx, void *mlx_win, int wid, int hei);
void 	ato_graphique(char **map, void *mlx_ptr, void *mlx_win_ptr);
void 	movingplayer(char **map, void *mlx, void *mlx_win);
void	launch_game(char **map, t_donne info);
void 	ft_putnbr(int nb);

#endif
