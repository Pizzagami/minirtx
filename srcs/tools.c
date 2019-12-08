/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 19:34:04 by selgrabl          #+#    #+#             */
/*   Updated: 2019/12/08 14:16:11 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

int				ft_atoi(char *str, int x)
{
	int i;
	int nb;
	int sign;

	sign = 1;
	i = 0 + x;
	nb = 0;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (str[i] >= '0' && str[i] <= '9')
			nb = nb * 10 + str[i] - 48;
		i++;
	}
	if (i == x)
		return(-42);
	return (nb * sign);
}

int 			ft_strlen(char *str)
{
	int i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

float			ft_atof(char buf[BUFFER_SIZE], int x)
{
    float   f;
    float   d;
    float   i;
    float   signe;

    f = 0;
    d = 0;
    i = 0;
    signe = (buf[x] == '-') ? -1 : 1;
	if (signe == -1)
		x++;
    while(buf[x] >= '0' && buf[x] <= '9')
        f = 10 * f + (buf[x++] - 48);
    if (buf[x] != ' ' && buf[x] !=  '.' && buf[x] != '\n' &&
		buf[x] != '\0' && buf[x] != ',')
        return(NAF);
    x = (buf[x] == '.')? x + 1: x;
	i = x;
    while(buf[x] > 47 && buf[x] < 58)
        d = 10 * d + (buf[x++] - 48);
    if (x - i > 0)
        while(x - i++ > 0)
            d /= 10;
    return((d + f) * signe);
}

float			read_float(char buf[BUFFER_SIZE], int *x)
{
	float ret;
	while (buf[*x] == ' ')
		(*x)++;
	ret = ft_atof(buf, *x);
	while ((buf[*x] >= '0' && buf[*x] <= '9') || buf[*x] == '-' ||
    buf[*x] == '.')
		(*x)++;
	while (buf[*x] == ' ')
		(*x)++;
	return (ret);
}

int			read_int(char buf[BUFFER_SIZE], int *x)
{
	int ret;

	while (buf[*x] == ' ')
		(*x)++;
	ret = ft_atoi(buf, *x);
	while ((buf[*x] >= '0' && buf[*x] <= '9') || buf[*x] == '-' ||
	buf[*x] == '.')
		(*x)++;
	while (buf[*x] == ' ')
		(*x)++;
		return(ret);
}