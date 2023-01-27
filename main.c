#include "so_long.h"

int	main(int ac, char *av[])
{
	char			*str;
	char			**map;
	char			**map_t;
	t_pos			end;
	t_donne 	info;

	if (ac != 2 || !(check_param(av[1])))
		err_msg("Sorry you can't join the game : Invalid name for map or not found !");
	//read from the file *.ber
	str = try2read_map(av[1]);
	if (!str)
		err_msg("Sorry you can't join tje game : A probleme in read map");
	//check data is valid
	first_map_check(str, &(info.data));
	//generat map whit the data
	map = ft_split(str, &(info.data));
	//ckeck map is valid
	second_map_check(map, info.data);
	//get player/end position
	get_position(map, 'P', &(info.player));
	get_position(map, 'E', &end);
	//test for a solution
	map_t = ft_split(str, &(info.data));
	check_a_solution(map_t, info.data, info.player.c, info.player.r);
	last_check(map_t, end);
	free(map_t);
	//graphics && rendering imgs
	launch_game(map, info);
	return (0);
}
