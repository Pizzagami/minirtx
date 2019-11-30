/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 19:34:04 by selgrabl          #+#    #+#             */
/*   Updated: 2019/11/30 18:18:57 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

int ft_atoi(char *str)
{
	int i;
	int nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			nb = nb * 10 + str[i] - 48;
		i++;
	}
	return (nb);
}

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}