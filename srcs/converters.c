/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raimbaultbrieuc <raimbaultbrieuc@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 10:07:31 by braimbau          #+#    #+#             */
/*   Updated: 2020/02/03 14:30:46 by raimbaultbr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

int		ft_atoi(char *str)
{
	int i;
	int nb;
	int sign;

	sign = 1;
	i = 0;
	nb = 0;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + str[i] - 48;
		i++;
	}
	if (str[i])
		return (-42);
	return (nb * sign);
}

float	ft_atof(char *buf)
{
	float	f;
	float	d;
	float	i;
	float	signe;
	int		x;

	x = 0;
	f = 0;
	d = 0;
	signe = (buf[x] == '-') ? -1 : 1;
	x = (signe == -1) ? x + 1 : x;
	while (buf[x] >= '0' && buf[x] <= '9')
		f = 10 * f + (buf[x++] - 48);
	if (buf[x] != ' ' && buf[x] != '.' && buf[x] != '\n' &&
		buf[x] != '\0' && buf[x] != ',')
		return (nanf("i"));
	x = (buf[x] == '.') ? x + 1 : x;
	i = x;
	while (buf[x] > 47 && buf[x] < 58)
		d = 10 * d + (buf[x++] - 48);
	if (x - i > 0)
		while (x - i++ > 0)
			d /= 10;
	return ((buf[x] || buf[x - 1] == '.') ? nanf("i") : (d + f) * signe);
}

char	*ft_itoa(int n)
{
	char	*na;
	int		i;
	int		max;
	long	nl;

	nl = n;
	i = 0;
	max = nb_char(nl);
	if (!(na = malloc((max + 1) * sizeof(char))))
		return (NULL);
	if (nl < 0)
	{
		na[0] = '-';
		nl *= -1;
		i++;
	}
	na[max] = 0;
	while (max > i)
	{
		na[max - 1] = (nl % 10) + 48;
		nl /= 10;
		max--;
	}
	return (na);
}
