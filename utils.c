#include "so_long.h"

int	ft_strlen(char *str, char set)
{
	int	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len] && str[len] != set)
		len++;
	return (len);
}

char	*ft_strjoin(char *s1, char *s2, int len)
{
	int i;
	int j;
	char *resl;

	i = 0;
	j = 0;
	if (!s2)
		return(NULL);
	resl = malloc((sizeof(char) * (len + 1)));
	while (s1 && s1[i])
	{
		resl[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		resl[i + j] = s2[j];
		j++;
	}
	resl[i + j] = '\0';
	if (!s1)
		free(s1);
	return (resl);
}

char	**ft_split(char *str, t_info *data)
{
	char	**resl;
	int	i;
	int j;
	int y;

	j = 0;
	i = 0;
	resl = malloc(sizeof(char *) * (data->row_len + 1));
	if (!resl)
		err_msg("malloc failed !");
	resl[data->row_len] = NULL;
	data->n_column = ft_strlen(str, '\n');
	while (resl && str[i])
	{
		y = 0;
		resl[j] = malloc(sizeof(char) * (data->n_column + 1));
		if (!resl)
			err_msg("malloc failed !");
		while (str[i + y] && str[i + y] != '\n')
		{
			resl[j][y] = str[i + y];
			y++;
		}
		resl[j][y] = '\0';
		if (!str[i + y])
			return (resl);
		i += y;
		j++;
		i++;
		if (str[i] && data->n_column != ft_strlen(&str[i], '\n'))
		err_msg("Sorry you can't join the game : The lines in the map are not compatible !");
	}
	return (resl);
}

void	get_position(char **map, char target, t_pos *position)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x] && map[y][x] != target)
			x++;
		if (map[y][x] == target)
			break ;
		y++;
	}
	position->r = y;
	position->c = x;
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
