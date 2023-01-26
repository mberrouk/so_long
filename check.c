#include "so_long.h"

int check_param(char *parm)
{
	int name_len;

	name_len = ft_strlen(parm, '\0');
	if ((name_len < 5) || parm[name_len - 1] != 'r' || parm[name_len - 2] != 'e' 
			|| parm[name_len - 3] != 'b' || parm[name_len - 4] != '.')
		return (0);
	return (1);
 }

void	err_msg(char *str)
{
	write(1, str, ft_strlen(str, '\0'));
	exit(1);
}

void	check_a_solution(char **map, t_info data, int x, int y)
{
	if (x >= data.n_column || x < 0 || y >= data.row_len || y < 0 
			|| map[y][x] == 'F' || map[y][x] == '1')
			return ;
	map[y][x] = 'F';
	check_a_solution(map, data, x + 1, y);
	check_a_solution(map, data, x - 1, y);
	check_a_solution(map, data, x, y + 1);
	check_a_solution(map, data, x, y - 1);
}

void	second_map_check(char **map, t_info data)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		if (i == 0 || (i == data.row_len - 1))
		{
			while (map[i][j])
			{
				if (map[i][j] != '1')
					err_msg("Sorry you can't join the game : Invalid walls !");
				j++;
			}
		}
		else
			if (map[i][0] != '1' || map[i][data.n_column - 1] != '1')
				err_msg("Sorry you can't join the game : Invalid walls !");
		i++;
	}
}

void	first_map_check(char *str, t_info *data)
{
	int i;
	int c;
	int p;
	int e;
	int	rlen;

	i = 0;
	c = 0;
	p = 0;
	e = 0;
	rlen = 0;
	while (str[i])
	{
		if ((i == 0 && str[i] == '\n') || (str[i] == '\n' && (str[i + 1] == '\n'))) 
			err_msg("Sorry you can't join the game : Invalid map !");
		if (str[i] == 'C')
			c++;
		else if (str[i] == 'E')
			e++;
		else if (str[i] == 'P')
			p++;
		if (str[i] && (str[i] != '\n' && (str[i + 1] == '\n' || !str[i + 1])))
			rlen++;
		if (str[i] != 'C' && str[i] != 'E' && str[i] != 'P' && str[i] != '0' && str[i] != '1' && str[i] != '\n')
			err_msg("Sorry you can't join the game : Invalid charcter in map !");
		i++;		
	}
	if (e != 1 || p != 1 || c < 1)
		err_msg("Sorry you can't join the game : more or less than characters !");
	data->n_collec = c;
	data->row_len = rlen;
}

