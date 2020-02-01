/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 13:13:56 by selgrabl          #+#    #+#             */
/*   Updated: 2020/02/01 10:06:30 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

void	print_vec(t_vec vec)
{
	printf("x : %f y : %f z : %f\n", vec.x, vec.y, vec.z);
}

void	print_vecs(int nbr, ...)
{
	va_list(ap);
	va_start(ap, nbr);
	while (nbr > 0)
	{
		print_vec(va_arg(ap, t_vec));
		nbr--;
	}
	va_end(ap);
}
