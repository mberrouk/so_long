#include "so_long.h"

void ft_putnbr(int nb)
{
  if (nb >= 10)
    ft_putnbr(nb / 10);
  write(1, &"0123456789"[nb % 10], 1);
}

void err_msg(char *str)
{
	write(1, str, ft_strlen(str, '\0'));
	exit(1);
}

