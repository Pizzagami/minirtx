/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 12:17:38 by selgrabl          #+#    #+#             */
/*   Updated: 2020/01/27 18:11:09 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"


int			distri(t_tg tri, t_vec p)
{
    int x;

    x = 1;
    x = (dot(tri.normal, cross(min(tri.p2, tri.p1), min(p, tri.p1))) >= 0) ? x: 0;
    x = (dot(tri.normal, cross(min(tri.p3, tri.p2), min(p, tri.p2))) >= 0) ? x: 0;
    x = (dot(tri.normal, cross(min(tri.p1, tri.p3), min(p, tri.p3))) >= 0) ? x: 0;
    return(x);
}

int			distsqr(t_tg shape, t_vec   dot)
{
    int x;

	x = distri(shape, dot);
	shape.p2 = shape.p4;
	if (x == 0)
	{
		shape.normal = fois(shape.normal, -1);
		x = distri(shape,dot);
	}
    return (x);
}

int			distce(t_tg shape, t_vec dot)
{
	return ((dist_dot(dot, shape.center) > (shape.dia)) ? 0: 1);
}

t_vec	find_normal(t_tg shape, t_cam cam, float dist)
{
	t_vec point;
	t_vec normal;

	point = plus(cam.origin, fois(cam.ray, dist));
	if (shape.type == 1 || shape.type == 11)
		normal = normalize(min(point, shape.center));
	else if (shape.type == 21 || shape.type == 32)
	{
		shape.v2 = (dot(shape.vec, min(point, shape.center)) < 0) ? fois(shape.vec, -1): shape.vec;
		shape.v1 = plus(fois(shape.v2, dist_dot(point, shape.center) / cos(shape.dia)), shape.center);
		normal = normalize(min(point, shape.v1));
	}
	else if (shape.type == 2)
		normal = normalize(min(point, plus(shape.center,fois(shape.vec, dot(min(point, shape.center), shape.vec)))));
	else
		normal = shape.normal;
	return(normal);
}