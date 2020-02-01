/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 12:17:38 by selgrabl          #+#    #+#             */
/*   Updated: 2020/02/01 10:38:01 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

int			second_degre(float a, float b, float c, float *x1, float *x2)
{
	float d;

	if (a == 0)
	{
		*x1 = - c / b;
		return (1);
	}
	d = pow(b, 2) - 4 * a * c;
	if (d < 0)
		return (0);
	else if (d == 0)
	{
		*x1 = -b / (2 * a);
		return (1);
	}
	else
	{
		*x1 = (-b + sqrt(d)) / (2 * a);
		*x2 = (-b - sqrt(d)) / (2 * a);
		return (2);
	}
}

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

void		create_tri(t_vec p1, t_vec p2, t_vec p3, t_rtx *rtx)
{
	t_tg *shape;
	t_tg tmp;

	tmp = *(rtx->shape);
	shape = malloc(sizeof(t_tg));
	shape->next = rtx->shape;
	rtx->shape = shape;
	rtx->shape->type = 3;
	rtx->shape->trans = tmp.trans;
	rtx->shape->refl = tmp.refl;
	rtx->shape->color = tmp.color;
	rtx->shape->p1 = p1;
	rtx->shape->p2 = p2;
	rtx->shape->p3 = p3;
	shape->normal = normalize(cross(min(shape->p2, shape->p1),
		min(shape->p3, shape->p1)));
	shape->center = shape->p1;
}