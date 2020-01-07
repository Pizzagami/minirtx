/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 12:17:38 by selgrabl          #+#    #+#             */
/*   Updated: 2020/01/06 16:56:54 by selgrabl         ###   ########.fr       */
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
	/*t_vec dot; POUR GAGNER ARGUMENT FAIRE DOT DEDANS ET AURE AUSSI?
    float a;
    float b;
    float c;
    float x;
    float s1;

    dot = min(origin, shape.center);
    a = pow(ray.x, 2) + pow(ray.z, 2) + pow(ray.y, 2);
    b = ray.x * dot.x + ray.z * dot.z + ray.y * dot.y;
    c = pow(dot.x, 2) + pow(dot.z, 2) + pow(dot.y, 2) - pow(shape.dia / 2, 2);

    x = pow(b, 2) - a * c;
    if( x == 0)
        return(-1.0);
    s1 = (-b -sqrtf(x)) / a;
    if( s1 == 0)
        return(-1.0);
    return s1;*/
}

int			distri(t_tg tri, t_vec p)
{
    int x;

    x = 1;
    x = (dot(tri.vec, cross(min(tri.p2, tri.p1), min(p, tri.p1))) >= 0) ? x: 0;
    x = (dot(tri.vec, cross(min(tri.p3, tri.p2), min(p, tri.p2))) >= 0) ? x: 0;
    x = (dot(tri.vec, cross(min(tri.p1, tri.p3), min(p, tri.p3))) >= 0) ? x: 0;
    return(x);
}

int			distsqr(t_tg shape, t_vec   dot)
{
    int x;

	x = distri(shape, dot);
	shape.p2 = shape.p4;
	if (x == 0)
	{
		shape.vec = fois(shape.vec, -1);
		x = distri(shape,dot);
	}
    return (x);
}

int			distce(t_tg shape, t_vec dot)
{
	return ((dist_dot(dot, shape.center) > (shape.dia)) ? 0: 1);
}