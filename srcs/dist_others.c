/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist_others.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 12:19:46 by braimbau          #+#    #+#             */
/*   Updated: 2020/02/03 10:23:31 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

float		find_dist_co(t_vec origin, t_vec ray, t_tg *sh, t_vec pos)
{
	t_vec v;
	float x;

	v.z = pow(cos(sh->dia), 2);
	v.x = pow(dot(ray, sh->vec), 2) - v.z;
	v.y = 2 * (dot(ray, sh->vec) * dot(pos, sh->vec) - dot(ray, pos) * v.z);
	v.z = pow(dot(pos, sh->vec), 2) - dot(pos, pos) * v.z;
	if ((x = pow(v.y, 2) - 4 * v.x * v.z) <= 0.00001)
		return (-1.0);
	v.z = (-v.y - sqrtf(x)) / (2 * v.x);
	v.x = (-v.y + sqrtf(x)) / (2 * v.x);
	if (v.x == 0 && v.z == 0)
		return (-1.0);
	v.y = (v.z < v.x && v.x > 0.0001) ? v.x : v.z;
	v.z = (v.z > v.x && v.x > 0.0001) ? v.x : v.z;
	v.x = dot(ray, sh->vec) * v.z + dot(pos, sh->vec);
	x = dot(min(sh->center, origin), sh->vec);
	if ((fabs(v.x) > sh->hi / 2) || (fabs(x) > sh->hi / 2 && v.z < 0))
	{
		v.x = dot(ray, sh->vec) * v.y + dot(pos, sh->vec);
		v.z = v.y;
		if ((fabs(v.x) > sh->hi / 2) || (fabs(x) > sh->hi / 2 && v.y < 0))
			return (-1.0);
	}
	return ((sh->type == 32 && v.x > 0) ? -1.0 : v.z);
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
