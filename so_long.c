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

int key_hook(int keycode, t_pos *var)
{
	printf("X");
	if (keycode == 2)
	{
		rendering_imgs("./floor.xpm", var->m, var->w, (var->c) * 60, (var->r) * 60);
		rendering_imgs("./player.xpm", var->m, var->w, (var->c += 1) * 60, (var->r) * 60);
	}
	else if (keycode == 0)
	{
		rendering_imgs("./floor.xpm", var->m, var->w, (var->c) * 60, (var->r) * 60);
		rendering_imgs("./player.xpm", var->m, var->w, (var->c -= 1) * 60, (var->r) * 60);
	}
	else if (keycode == 13)
	{
		rendering_imgs("./floor.xpm", var->m, var->w, (var->c) * 60, (var->r) * 60);
		rendering_imgs("./player.xpm", var->m, var->w, (var->c) * 60, (var->r -= 1) * 60);
	}
	else if (keycode == 1)
	{
		rendering_imgs("./floor.xpm", var->m, var->w, (var->c) * 60, (var->r) * 60);
		rendering_imgs("./player.xpm", var->m, var->w, (var->c) * 60, (var->r += 1) * 60);
	}
		return (0);
}

void movingplayer(char **map, void *mlx, void *mlx_win)
{
	t_vars vars;
	t_pos player;
	int key;
	int (*ptr)(int, t_vars *) = key_hook;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 640, 480, "Hello world!");
	get_position(map, 'P', &player);
	mlx_key_hook(vars.win, ptr, &vars);
	mlx_loop(vars.mlx);
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

void 	last_check(char **map)
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
					&& map[y][x] != '0')
			{
				ft_clean(map);
				err_msg("Invalid map : you can't win the game!");
			}
			x++;
		}
		y++;
	}
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

