/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 12:17:38 by selgrabl          #+#    #+#             */
/*   Updated: 2019/12/20 05:39:24 by selgrabl         ###   ########.fr       */
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
    x = (dot(tri.vec, cross(min(tri.p2, tri.p1), min(p, tri.p1))) > 0) ? x: 0;
    x = (dot(tri.vec, cross(min(tri.p3, tri.p2), min(p, tri.p2))) > 0) ? x: 0;
    x = (dot(tri.vec, cross(min(tri.p1, tri.p3), min(p, tri.p3))) > 0) ? x: 0;
    return(x);
}

int			distsqr(t_vec   dot, t_tg shape)
{
    int x;
    t_vec v1;
	t_vec v2;

	v1.y = 0;
	v1.x = (shape.vec.z == 0) ? 0 : 1;
	v1.z = (shape.vec.x == 0 && v1.x == 1) ? 0 : 1;
	v1.z = (shape.vec.x && shape.vec.z)? -shape.vec.x / shape.vec.z: v1.z;
	v1 = normalize(v1);
	v2 = normalize(cross(shape.vec, v1));
    corners(&shape);
	//print_vecs(4, shape.p1, shape.p2, shape.p3, shape.vec);
	shape.vec = fois(shape.vec, -1);
	x = distri(shape,dot);
	//printf("%d\n", x);
	shape.p2 = shape.p4;
	if (x == 0)
	{
		shape.vec = fois(shape.vec, -1);
		x = distri(shape,dot);
	}

    /*if(shape.p1.y > shape.p2.y)
		x = between(v1,shape.p1,shape.p2,dot, x);
    else
		x = between(v1,shape.p2,shape.p1,dot, x);
    if(shape.p1.y > shape.p2.y)
		x = (dot.y <= shape.p1.y && dot.y >= shape.p2.y) ? x: 1;
    else
		x = (dot.y >= shape.p1.y && dot.y <= shape.p2.y) ? x: 1;
	 if(shape.p1.y > shape.p2.y)
		x = between(v2, shape.p1, shape.p2, dot, x);
    else
		x = between(v2, shape.p2,shape.p1, dot, x);*/
    return (x);
}

float		find_dist_sp(t_vec   origin, t_vec ray, t_tg shape)
{
    float x1;
    float x2;
    int s;

    x2 = 0;
    s = second_degre(dot(ray, ray),2 * dot(ray,
    min(origin, shape.center)),dot(min(origin, shape.center),
    min(origin, shape.center)) - pow(shape.dia/2, 2), &x1, &x2);
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

float		find_dist_stp(t_vec   origin, t_vec ray, t_tg shape)
{
    float x;

	shape.center = (shape.type == 3) ? shape.p1 :shape.center;
    x = (dot(ray, shape.vec) != 0) ?(dot(min(shape.center, origin),
        shape.vec)/ dot(ray, shape.vec)) : 0;
    if (shape.type == 4)
        x = (distsqr(plus(origin, fois(ray, x)), shape) == 1) ? x: 0;
    if (shape.type == 3)
        x = (distri(shape, plus(origin, fois(ray, x))) == 1) ? x : 0;
    return((x > 0.0) ? x : -1.0);
}

float		find_dist_ce(t_vec   origin, t_vec ray, t_tg shape)
{
	float x;

	x = find_dist_stp(origin, ray, shape);
	x = (dist_dot(plus(origin, fois(ray, x)), shape.center) >
	shape.dia / 2)? 0: x;
    return((x > 0.0) ? x : -1.0);
}
float		find_dist_cy(t_vec   origin, t_vec ray, t_tg shape)
{
	origin.x = ray.x + shape.type;
	return(0.0);
}