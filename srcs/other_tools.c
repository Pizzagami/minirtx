/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 14:19:00 by braimbau          #+#    #+#             */
/*   Updated: 2020/02/03 10:44:55 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

int		nb_char(long n)
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

void	init_lst(t_rtx *rtx)
{
	rtx->shape = NULL;
	rtx->cam = NULL;
	rtx->light = NULL;
}

void	make_mapping(t_tg *shape)
{
	float u;
	float v;
	float theta;

	if (shape->type != 11)
		return ;
	v = acos(-dot(shape->v1, shape->normal)) / M_PI;
	theta = (acos(dot(shape->normal, shape->v2) / sin(acos(-dot(shape->v1,
	shape->normal))))) / (2 * M_PI);
	if (dot(cross(shape->v1, shape->v2), shape->normal) > 0)
		u = theta;
	else
		u = 1 - theta;
	shape->color = cp(u * shape->map_res.x, v * shape->map_res.y,
	shape->map_id, shape->map_res);
	shape->color.r = (unsigned char)shape->color.r;
	shape->color.g = (unsigned char)shape->color.g;
	shape->color.b = (unsigned char)shape->color.b;
}

t_res	init_res(int x, int y)
{
	t_res r;

	r.x = x;
	r.y = y;
	return (r);
}
