#include "so_long.h"

void 	rendering_imgs(char *filename, void *mlx, void *mlx_win, int wid, int hei)
{
	t_data img;
	int width;
	int height;
	
	img.img = mlx_xpm_file_to_image(mlx, filename, &width, &height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, 
			&img.endian);
	mlx_put_image_to_window(mlx, mlx_win, img.img, wid, hei);
}

int get_in_step(int keycode, t_donne *var)
{
	int c;
	int r;
	
	r = var->player.r;
	c = var->player.c;
	if (keycode == 2)
		c += 1;
	else if (keycode == 0)
		c -= 1;
	else if (keycode == 13)
 		r -= 1;
	else if (keycode == 1)
		r += 1;
	if (var->map[r][c] == '1' || (var->map[r][c] == 'E' && var->data.n_collec))
		return (0);
	if (var->map[r][c] == 'C')
	{
		var->map[r][c] = '0';
		var->data.n_collec -= 1;
	}
	var->player.c = c;
	var->player.r = r;
	return (1);
}

int key_hook(int keycode, t_donne *var)
{
	int c;
	int r;

	r = var->player.r;
	c = var->player.c;
	if (!get_in_step(keycode, var))
		return  (0);
	rendering_imgs("./floor.xpm", var->mlx, var->win, c * 60, r * 60);
	rendering_imgs("./player.xpm", var->mlx, var->win, (var->player.c) * 60, (var->player.r) * 60);
	return (0);
}

void 	launch_game(char **map, t_donne info)
{
	void *mlx;
	void *mlx_win;
	t_pos pla;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, info.data.n_column * 60, info.data.row_len * 60, "|SO_LONG|");
	info.mlx = mlx;
	info.win = mlx_win;
	info.map = map;
	ato_graphique(map, mlx, mlx_win);
	mlx_hook(mlx_win, 2, 0, key_hook, &info);
	mlx_loop(mlx);
}

void 	ato_graphique(char **map, void *mlx_ptr, void *mlx_win_ptr)
{
	int x;
	int y;

	y = 0;
		while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
					rendering_imgs("./wall.xpm", mlx_ptr, mlx_win_ptr, 60 * x, 60 * y);		
			else if (map[y][x] == '0')
					rendering_imgs("./floor.xpm", mlx_ptr, mlx_win_ptr, 60 * x, 60 * y);
			else if (map[y][x] == 'C')
					rendering_imgs("./coin.xpm", mlx_ptr, mlx_win_ptr, 60 * x, 60 * y);
			else if (map[y][x] == 'P')
					rendering_imgs("./player.xpm", mlx_ptr, mlx_win_ptr, 60 * x, 60 * y);
			else if (map[y][x] == 'E')
					rendering_imgs("./door.xpm", mlx_ptr, mlx_win_ptr, 60 * x, 60 * y);
			x++;
		}
		y++;
	}
}

void 	last_check(char **map, t_pos E)
{
	int	x;
	int y;
	
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] && map[y][x] != 'F' && map[y][x] != '1'
					&& map[y][x] != '0' && map[y][x] != 'E')
			{
				ft_clean(map);
				err_msg("Invalid map : you can't win the game!");
			}
			x++;
		}
		y++;
	}
	if (map[E.r][E.c - 1] != 'F' && map[E.r][E.c + 1] != 'F' 
						&& map[E.r - 1][E.c] != 'F' && map[E.r + 1][E.c] != 'F')
						err_msg("Invalid map : you can't win the game!");

}

char *try2read_map(char *name_file)
{
	char	*buf;
	char	*map;
	int	n_rbit;
	int	fd;
	int len;
	
	fd = open(name_file, O_RDONLY);
	buf = malloc(sizeof(char) * 11);
	n_rbit = 1;
	map = NULL;
	len = 0;
	while (n_rbit)
	{
		n_rbit = read(fd, buf, 10);
		if (n_rbit < 0)
		{
			if (map)
				free(map);
			free(buf);
			return (NULL);
		}
		buf[n_rbit] = '\0';
		len += n_rbit;
		if (n_rbit)
			map = ft_strjoin(map, buf, len);
	}
	free(buf);
	return (map);
}

