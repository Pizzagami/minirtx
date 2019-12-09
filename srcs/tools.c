/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 19:34:04 by selgrabl          #+#    #+#             */
/*   Updated: 2019/12/09 18:47:57 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

int		ft_atoi(char *str, int *x)
{
	int i;
	int nb;
	int sign;

	sign = 1;
	i = 0 + *x;
	nb = 0;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
		(*x)++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + str[i] - 48;
		i++;
		(*x)++;
	}
	if (i == *x)
		return(-42);
		printf("_%c_\n", str[i]);
	if (str[i + 1])
		*x = (str[i] == ',') ? i + 1: 0;
	return (nb * sign);
}

int 		ft_strlen(char *str)
{
	int i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

void	ft_putstr(char *str)
{
	int i;

	i = 0;
	while(str && str[i])
		i++;
	write(0, str, i);
}

float		ft_atof(char *buf, int *x)
{
    float   f;
    float   d;
    float   i;
    float   signe;

    f = 0;
    d = 0;
    signe = (buf[*x] == '-') ? -1 : 1;
	if (signe == -1)
		(*x)++;
    while(buf[*x] >= '0' && buf[*x] <= '9')
        f = 10 * f + (buf[(*x)++] - 48);
    if (buf[*x] != ' ' && buf[*x] !=  '.' && buf[*x] != '\n' &&
		buf[*x] != '\0' && buf[*x] != ',')
        return(NAF);
    *x = (buf[*x] == '.')? *x + 1: *x;
	i = *x;
    while(buf[*x] > 47 && buf[*x] < 58)
        d = 10 * d + (buf[(*x)++] - 48);
    if (*x - i > 0)
        while(*x - i++ > 0)
            d /= 10;
	if (buf[*x])
		*x = (buf[(*x) - 1] == ',') ? *x: 0;
    return((d + f) * signe);
}

void	ft_putnbr(int nb)
{
	unsigned int	nbr;
	char			a;
	if (nb < 0)
	{
		ft_putstr("-");
		nbr = (unsigned int)(nb * -1);
	}
	else
		nbr = (unsigned int)nb;
	if (nbr >= 10)
		ft_putnbr(nbr / 10);
	a = nbr % 10 + 48;
	write(0, &a,1);
}