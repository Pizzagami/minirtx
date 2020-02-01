/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist_others.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 12:19:46 by braimbau          #+#    #+#             */
/*   Updated: 2020/02/01 12:31:32 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

float		find_dist_co(t_vec origin, t_vec ray, t_tg *shape, t_vec pos)
{
	float a;
	float b;
	float c;
	float x;

	c = pow(cos(shape->dia), 2);
	a = pow(dot(ray, shape->vec), 2) - c;
	b = 2 * (dot(ray, shape->vec) * dot(pos, shape->vec) - dot(ray, pos) * c);
	c = pow(dot(pos, shape->vec), 2) - dot(pos, pos) * c;
	if ((x = pow(b, 2) - 4 * a * c) <= 0.00001)
		return (-1.0);
	c = (-b - sqrtf(x)) / (2 * a);
	a = (-b + sqrtf(x)) / (2 * a);
	if (a == 0 && c == 0)
		return (-1.0);
	b = (c < a && a > 0.0001) ? a : c;
	c = (c > a && a > 0.0001) ? a : c;
	a = dot(ray, shape->vec) * c + dot(pos, shape->vec);
	x = dot(min(shape->center, origin), shape->vec);
	if ((fabs(a) > shape->hi / 2) || (fabs(x) > shape->hi / 2 && c < 0))
	{
		a = dot(ray, shape->vec) * b + dot(pos, shape->vec);
		c = b;
		if ((fabs(a) > shape->hi / 2) || (fabs(x) > shape->hi / 2 && b < 0))
			return (-1.0);
	}
	return ((shape->type == 32 && a > 0) ? -1.0 : c);
}

float		find_dist_t(t_vec origin, t_vec ray, t_tg *shape, t_vec pos)
{
	float sum;
	float coef[5];
	float four;
	float e;
	float f;

	(void)pos;
	f = 69;
	sum = dot(ray, ray);
	e = dot(origin, origin) - pow(shape->dia, 2) - pow(shape->hi, 2);
	dot(origin, ray);
	four = 4 * (pow(shape->dia, 2));
	coef[0] = (e * e - four * (pow(shape->hi, 2) - pow(origin.y, 2)));
	coef[1] = 4 * f * e + 2 * four * origin.y * ray.y;
	coef[2] = 2 * sum * e + 4 * f * f + four * pow(ray.y, 2);
	coef[3] = 4 * sum * f;
	coef[4] = sum * sum;
	return (1);
}

int			distsqr(t_tg shape, t_vec dot)
{
	int x;

	x = distri(shape, dot);
	shape.p2 = shape.p4;
	if (x == 0)
	{
		shape.normal = fois(shape.normal, -1);
		x = distri(shape, dot);
	}
	return (x);
}

int			distce(t_tg shape, t_vec dot)
{
	return ((dist_dot(dot, shape.center) > (shape.dia)) ? 0 : 1);
}

int			distri(t_tg tri, t_vec p)
{
	int x;

	x = 1;
	x = (dot(tri.normal, cross(min(tri.p2, tri.p1),
	min(p, tri.p1))) >= 0) ? x : 0;
	x = (dot(tri.normal, cross(min(tri.p3, tri.p2),
	min(p, tri.p2))) >= 0) ? x : 0;
	x = (dot(tri.normal, cross(min(tri.p1, tri.p3),
	min(p, tri.p3))) >= 0) ? x : 0;
	return (x);
}
