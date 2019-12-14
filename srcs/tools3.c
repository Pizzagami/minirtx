/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 14:19:00 by braimbau          #+#    #+#             */
/*   Updated: 2019/12/14 13:19:43 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

int		ft_strcmp(char *s1, char *s2)
{
	unsigned int i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - s2[i]);
		i++;
	}
	if (((s1[i] == '\0' && s2[i] != '\0') ||
				(s2[i] == '\0' && s1[i] != '\0')))
		return ((unsigned char)s1[i] - s2[i]);
	return (0);
}

char	*check_ligne(char *str)
{
	int i;

	i = 1;
	while(str[i])
	{
		if (str[i] == ',' && str[i - 1] == ',')
			return("Invalid line format");
		i++;
	}
	return(NULL);
}

int	nb_char(long n)
{
	long	c;
	int		r;

	c = 10;
	r = 1;
	if (n < 0)
	{
		r++;
		n *= -1;
	}
	while (n >= c)
	{
		c = c * 10;
		r++;
	}
	return (r);
}

char		*ft_itoa(int n)
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

void	init_lst(t_rtx *rtx)
{
	rtx->shape = NULL;
	rtx->cam = NULL;
	rtx->light = NULL;
}
