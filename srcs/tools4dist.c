/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4dist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 14:10:01 by selgrabl          #+#    #+#             */
/*   Updated: 2020/01/23 15:55:09 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

float		find_dist(t_vec origin, t_vec ray, t_tg *shape)
{
	if (shape->type == 1)
		return (find_dist_sp(origin, ray, *shape));
	if (shape->type == 2)
		return (find_dist_cy(origin, ray, shape, min(origin, shape->center)));
	if (shape->type == 21)
		return (find_dist_sa(origin, ray, shape, min(origin, shape->center)));
	if (shape->type == 32)
		return (find_dist_co(origin, ray, shape, min(origin, shape->center)));
	return (find_dist_stcp(origin, ray, *shape));
}

float		find_dist_sp(t_vec origin, t_vec ray, t_tg shape)
{
	float	x1;
	float	x2;
	int		s;

	x2 = 0;
	s = second_degre(dot(ray, ray), 2 * dot(ray,
	min(origin, shape.center)), dot(min(origin, shape.center),
	min(origin, shape.center)) - pow(shape.dia / 2, 2), &x1, &x2);
	if (s == 1 && x1 > 0.0)
		return (x1);
	else if (s == 2 && (x1 > 0.0 || x2 > 0.0))
	{
		if (x2 > 0.0)
			return ((x1 <= x2 && x1 > 0.0) ? x1 : x2);
		return (x1);
	}
	return (-1.0);
}

float		find_dist_stcp(t_vec origin, t_vec ray, t_tg shape)
{
	float x;
	x = (dot(ray, shape.normal) != 0) ? (dot(min(shape.center, origin),
		shape.normal) / dot(ray, shape.normal)) : 0;
	if (shape.type == 7)
		x = (distce(shape, plus(origin, fois(ray, x))) == 1) ? x : 0;
	else if (shape.type == 4)
		x = (distsqr(shape, plus(origin, fois(ray, x))) == 1) ? x : 0;
	else if (shape.type == 3)
		x = (distri(shape, plus(origin, fois(ray, x))) == 1) ? x : 0;
	return ((x > 0) ? x : -1.0);
}

float		find_dist_cy(t_vec origin, t_vec ray, t_tg *shape, t_vec pos)
{
	float a;
	float b;
	float c;
	float x;
	t_vec point;

	a = dot(ray, ray) - dot(ray, shape->vec) * dot(ray, shape->vec);
	b = 2 * (dot(ray, pos) - dot(ray, shape->vec) * dot(pos, shape->vec));
	c = dot(pos, pos) - pow(dot(pos, shape->vec), 2) - pow(shape->dia / 2, 2);
	if ((x = pow(b, 2) - 4 * a * c) <= 0.00001)
		return (-1.0);
	c = (-b - sqrtf(x)) / (2 * a);
	a = (-b + sqrtf(x)) / (2 * a);
	if (a == 0 && c == 0)
		return (-1.0);
	shape->p1.x = (c > a) ? -1 : 1;
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
	point = plus(origin, fois(ray, c));
	shape->normal = normalize(min(point, plus(shape->center,
	fois(shape->vec, dot(min(point, shape->center), shape->vec))))); //-1
	return (c);
}

float		find_dist_sa(t_vec origin, t_vec ray, t_tg *shape, t_vec pos)
{
	float a;
	float b;
	float c;
	float x;
	t_vec point;
	
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
	point = plus(origin, fois(ray, c));
	shape->v2 = (dot(shape->vec, min(point, shape->center)) < 0) ? fois(shape->vec, -1): shape->vec;
	shape->v1 = plus(fois(shape->v2, dist_dot(point, shape->center) / cos(shape->dia)), shape->center);
	shape->normal = normalize(min(point, shape->v1)); // - quand dedans
	return (c);
}

float		find_dist_co(t_vec origin, t_vec ray, t_tg *shape, t_vec pos)
{
	float a;
	float b;
	float c;
	float x;
	t_vec point;

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
	x = (c < a) ? a : c;
	b = (c > a) ? c : a;
	c = (x < 0.0001) ? b : x;
	point = plus(origin, fois(ray, c));
	a = dot(ray, shape->vec) * c + dot(pos, shape->vec);
	shape->v2 = (dot(shape->vec, min(point, shape->center)) < 0) ? fois(shape->vec, -1): shape->vec;
	shape->v1 = plus(fois(shape->v2, dist_dot(point, shape->center) / cos(shape->dia)), shape->center);
	shape->normal = normalize(min(point, shape->v1)); // - quand dedans
	return (c);
}