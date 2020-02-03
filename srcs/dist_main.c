/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 14:10:01 by selgrabl          #+#    #+#             */
/*   Updated: 2020/02/01 12:25:57 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

float		find_dist(t_vec origin, t_vec ray, t_tg *shape)
{
	if (shape->type == 1 || shape->type == 11)
		return (find_dist_sp(origin, ray, *shape));
	if (shape->type == 2)
		return (find_dist_cy(origin, ray, shape, min(origin, shape->center)));
	if (shape->type == 21 || shape->type == 32)
		return (find_dist_co(origin, ray, shape, min(origin, shape->center)));
	if (shape->type == 42)
		return (find_dist_t(origin, ray, shape, min(origin, shape->center)));
	return (find_dist_stcp(origin, ray, *shape));
}

float		find_dist_sp(t_vec origin, t_vec ray, t_tg shape)
{
	float	x1;
	float	x2;
	int		s;

	x2 = 0;
	s = second_degre(init_vec(dot(ray, ray), 2 * dot(ray,
	min(origin, shape.center)), dot(min(origin, shape.center),
	min(origin, shape.center)) - pow(shape.dia / 2, 2)), &x1, &x2);
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
	t_vec v;
	float x;

	v.x = dot(ray, ray) - dot(ray, shape->vec) * dot(ray, shape->vec);
	v.y = 2 * (dot(ray, pos) - dot(ray, shape->vec) * dot(pos, shape->vec));
	v.z = dot(pos, pos) - pow(dot(pos, shape->vec), 2) - pow(shape->dia / 2, 2);
	if ((x = pow(v.y, 2) - 4 * v.x * v.z) <= 0.00001)
		return (-1.0);
	v.z = (-v.y - sqrtf(x)) / (2 * v.x);
	v.x = (-v.y + sqrtf(x)) / (2 * v.x);
	if (v.x == 0 && v.z == 0)
		return (-1.0);
	shape->p1.x = (v.z > v.x) ? -1 : 1;
	v.y = (v.z < v.x && v.x > 0.0001) ? v.x : v.z;
	v.z = (v.z > v.x && v.x > 0.0001) ? v.x : v.z;
	v.x = dot(ray, shape->vec) * v.z + dot(pos, shape->vec);
	x = dot(min(shape->center, origin), shape->vec);
	if ((fabs(v.x) > shape->hi / 2) || (fabs(x) > shape->hi / 2 && v.z < 0))
	{
		v.x = dot(ray, shape->vec) * v.y + dot(pos, shape->vec);
		v.z = v.y;
		if ((fabs(v.x) > shape->hi / 2) || (fabs(x) > shape->hi / 2 && v.y < 0))
			return (-1.0);
	}
	return (v.z);
}
