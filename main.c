#include "so_long.h"

int	handle_no_event(void *data)
{
	/* This function needs to exist, but it is useless for the moment */
	return (0);
}

int	main(int ac, char *av[])
{
	char	*str;
	char	**map;
	char	**map_t;

	t_info	data;
	t_pos	player;
	t_pos	end;

	if (ac != 2 || !(check_param(av[1])))
		err_msg("Sorry you can't join the game : Invalid name for map or not found !");
	
	//read from the file *.ber
	str = try2read_map(av[1]);
	if (!str)
		err_msg("Sorry you can't join tje game : A probleme in read map");
	
	//check data is valid
	first_map_check(str, &data);
	
	//generat map whit the data
	map = ft_split(str, &data);

	//ckeck map is valid
	second_map_check(map, data);
	
	//get player/end position
	get_position(map, 'P', &player);
	get_position(map, 'E', &end);

	//test1 for a solution
	map_t = ft_split(str, &data);
	check_a_solution(map_t, data, player.c, player.r);
	last_check(map_t);
	free(map_t);

	//test2
	map_t = ft_split(str, &data);
	map_t[end.r][end.c] = '1';
	check_a_solution(map_t, data, player.c, player.r);
	last_check(map_t);
	free(map_t);
	
	//graphics && rendering imgs
	void	*mlx;
	void	*mlx_win;
	t_vars vars;
	t_vars info;
	t_pos pla;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, data.n_column * 60, data.row_len * 60, "Hello world!");
	pla.m = mlx;
	pla.w = mlx_win;
	pla.c = player.c;
	pla.r = player.r;
	ato_graphique(map, mlx, mlx_win);
//	mlx_loop_hook(vars.mlx, &handle_no_event, &vars);
	mlx_hook(mlx_win, 2, 0, key_hook, &pla);
//	movingplayer(map, mlx, mlx_win);
	mlx_loop(mlx);
//	mlx_destroy_display(vars.mlx);
	return (0);
}
