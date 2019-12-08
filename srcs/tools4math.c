/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 12:17:38 by selgrabl          #+#    #+#             */
/*   Updated: 2019/12/08 14:09:00 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

int		second_degre(float a, float b, float c, float *x1, float *x2)
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

int     distri(t_tg tri, t_vec p)
{
    int x;

    x = 1;
    x = (dot(tri.vec, cross(min(tri.p2, tri.p1), min(p, tri.p1))) > 0) ? x: 0;
    x = (dot(tri.vec, cross(min(tri.p3, tri.p2), min(p, tri.p2))) > 0) ? x: 0;
    x = (dot(tri.vec, cross(min(tri.p1, tri.p3), min(p, tri.p3))) > 0) ? x: 0;
    return(x);
}

int     distsqr(t_vec   dot, t_vec center, float hi, t_vec vec)
{
    int x;

    hi /= 2;
    vec = xfois(vec, hi);
    x = 0;
    x = ((dot.x <= (center.x + vec.x)) && (dot.x >= (center.x - vec.x)))? x: 1;
    x = ((dot.y <= (center.y + vec.y)) && (dot.y >= (center.y - vec.y))) ? x: 1;
    return (x);
}

float find_dist(t_vec origin, t_vec ray, t_tg shape)
{
    float x1;
    float x2;
    int s;

    x2 = 0;
    s = 1;
    shape.center = (shape.type == 3) ? shape.p1 :shape.center;
    if (shape.type == 1)
    s = second_degre(dot(ray, ray),2 *dot(ray,
    min(origin, shape.center)),dot(min(origin, shape.center),
    min(origin, shape.center)) - pow(shape.dia/2, 2), &x1, &x2);
    if (shape.type == 0 || shape.type == 4 || shape.type == 3)
        x1 = (dot(ray, shape.vec) != 0) ?(dot(min(shape.center, origin),
        shape.vec)/ dot(ray, shape.vec)) : 0;
    if (shape.type == 4)
        x1 = (distsqr(plus(origin, fois(ray, x1)), shape.center,
        shape.hi, shape.vec) > 0) ? 0: x1;
    if (shape.type == 3)
        x1 = (distri(shape, plus(origin, fois(ray, x1))) == 1) ? x1 : 0;
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