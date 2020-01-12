/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4aa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 10:38:58 by braimbau          #+#    #+#             */
/*   Updated: 2020/01/11 16:28:44 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

void    anti_aliesing(t_res res, char **id)
{
	int     x;
	int     y;

	x = 0;
	while (x < res.x)
	{
		y = 0;
		while (y < res.y)
		{
			if (x && y && x != res.x - 1 && y != res.y - 1)
			{
			(*id)[(x + (y * res.x)) * 4] /= 2;//(char) (*id)[(x + (y * res.x)) * 4]/2;
			(*id)[((x + (y * res.x)) * 4) + 1] /= 2;//(char) (*id)[((x + (y * res.x)) * 4) + 1]/2;
			(*id)[((x + (y * res.x)) * 4 )+ 2] /= 2;//(char) (*id)[((x + (y * res.x)) * 4 )+ 2]/2;
			}
			else
			(*id)[(x + (y * res.x)) * 4] = (*id)[(x + (y * res.x)) * 4];
			(*id)[((x + (y * res.x)) * 4) + 1] = (*id)[((x + (y * res.x)) * 4) + 1];
			(*id)[((x + (y * res.x)) * 4 )+ 2] = (*id)[((x + (y * res.x)) * 4 )+ 2];
			y++;
		}
		x++;
	}
}