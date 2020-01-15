/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 12:17:38 by selgrabl          #+#    #+#             */
/*   Updated: 2020/01/15 15:57:12 by selgrabl         ###   ########.fr       */
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