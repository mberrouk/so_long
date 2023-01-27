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
	static int step;
	
	r = var->player.r;
	c = var->player.c;
	if (keycode == 53)
		exit(1);
	if (keycode == 2 || keycode == 124)
		c += 1;
	else if (keycode == 0 || keycode == 123)
 		c -= 1;
	else if (keycode == 13 || keycode == 126)
 		r -= 1;
	else if (keycode == 1 || keycode == 125)
		r += 1;
	if (var->map[r][c] == '1' || (var->map[r][c] == 'E' && var->data.n_collec))
		return (0);
	if (var->map[r][c] == 'C')
	{
		var->map[r][c] = '0';
		var->data.n_collec -= 1;
	}
	ft_putnbr(++step);
	write(1, "\n", 1);
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
	if (var->map[var->player.r][var->player.c] == 'E')
			exit(1);
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
