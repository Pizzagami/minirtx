/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 12:17:38 by selgrabl          #+#    #+#             */
/*   Updated: 2019/11/29 17:03:18 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

int second_degre(float a, float b, float c, float *x1, float *x2)
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

t_vec normalize(t_vec vect)
{
	t_vec tmp;

	tmp = vect;
	vect.x = vect.x / sqrtf(dot(tmp, tmp));
	vect.y = vect.y / sqrtf(dot(tmp, tmp));
	vect.z = vect.z / sqrtf(dot(tmp, tmp));
	return(vect);
}

t_vec	min(t_vec truc, t_vec machin)
{
	truc.x -= machin.x;
	truc.y -= machin.y;
	truc.z -= machin.z;

	return (truc);
}

float	dot(t_vec machin, t_vec bidule)
{
	return(machin.x * bidule.x + machin.y * bidule.y + machin.z * bidule.z);
}

t_vec	plus(t_vec truc, t_vec machin)
{
	truc.x += machin.x;
	truc.y += machin.y;
	truc.z += machin.z;
	return (truc);
}

t_vec	fois(t_vec truc, float a)
{
	truc.x *= a;
	truc.y *= a;
	truc.z *= a;
	return (truc);
}


float find_dist(t_cam cam, t_tg shape)
{
	float x1;
	float x2;
	int s;

	s = second_degre(dot(cam.ray, cam.ray),
	 2 * dot(cam.ray,min(cam.origin, shape.center)),
	 dot(min(cam.origin, shape.center),
	min(cam.origin, shape.center)) - pow(shape.dia/2, 2), &x1, &x2);
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