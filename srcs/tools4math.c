/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 12:17:38 by selgrabl          #+#    #+#             */
/*   Updated: 2019/12/04 18:28:24 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

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

t_color	lfois(t_color color, float a)
{
	color.r *= a;
	color.g *= a;
	color.b *= a;
	return (color);
}
t_vec	rotation(t_vec truc) /////ROTATION FAUX
{
	float tmp;
	tmp = truc.x;
	truc.z =  truc.x;
	truc.x = truc.z;
	truc.y = tmp ;
	return (truc);
}

int		inter(t_vec	dot, t_vec center, float hi, t_vec vec)
{
	int x;

	//hi /= 2;
	vec = fois(rotation(vec), hi);

	x = 0;
	x = ((dot.x <= (center.x + vec.x)) && (dot.x >= (center.x - vec.x)))? x: 1;
		vec = fois(rotation(vec), hi);
	x = ((dot.y <= (center.y + vec.y)) && (dot.y >= (center.y - vec.y))) ? x: 1;
	return (x);
}
float find_dist(t_cam cam, t_tg shape)
{
	float x1;
	float x2;
	int s;

	x2 = 0;
	s = 1;
	if (shape.type == 1)
	s = second_degre(dot(cam.ray, cam.ray),2 *dot(cam.ray,
	min(cam.origin, shape.center)),dot(min(cam.origin, shape.center),
	min(cam.origin, shape.center)) - pow(shape.dia/2, 2), &x1, &x2);
	if (shape.type == 0 || shape.type == 4)
	x1 = (dot(cam.ray, shape.vec) != 0) ?(dot(min(shape.center, cam.origin), shape.vec)/
	dot(cam.ray, shape.vec)) : 0;
	if (shape.type == 4)
	x1 = (inter(plus(cam.origin, fois(cam.ray, x1)), shape.center, shape.hi, shape.vec) > 0) ? 0: x1;
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
