/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 09:53:07 by braimbau          #+#    #+#             */
/*   Updated: 2020/02/01 10:01:41 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

void	ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str && str[i])
		i++;
	write(0, str, i);
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
	write(0, &a, 1);
}