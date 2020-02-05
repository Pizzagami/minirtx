/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 10:50:08 by braimbau          #+#    #+#             */
/*   Updated: 2020/02/04 17:35:34 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

t_color		cosha(float ratio, t_color light, t_color shape)
{
	t_color color;

	color.r = ratio * (unsigned char)light.r / 255 * (unsigned char)shape.r;
	color.g = ratio * (unsigned char)light.g / 255 * (unsigned char)shape.g;
	color.b = ratio * (unsigned char)light.b / 255 * (unsigned char)shape.b;
	return (color);
}

t_color		color_mix(t_color c1, t_color c2, float r1, float r2)
{
	t_color color;

	color.r = c1.r * r1 + c2.r * r2;
	color.g = c1.g * r1 + c2.g * r2;
	color.b = c1.b * r1 + c2.b * r2;
	return (color);
}

void		damier(t_vec point, t_tg *shape, t_color *color)
{
	t_vec right;
	t_vec up;
	float t;
	float t2;

	point = plus(point, init_vec(214748,214748,214748));
	right = normalize(cross(shape->normal, init_vec(0, 1, 0)));
	if (isnan(right.x) && isnan(right.z) && isnan(right.y))
		right = (shape->normal.y > 0) ? init_vec(1, 0, 0) : init_vec(-1, 0, 0);
	up = normalize(cross(right, shape->normal));
	t = dot(right, point);
	t2 = dot(up, point);
	if ((((int)(t / shape->dam) % 2 == 0) + ((int)(t2 / shape->dam) % 2 == 0)) == 1)
	{
		color->r = 255 - color->r;
		color->g = 255 - color->g;
		color->b = 255 - color->b;
	}
}

t_color		cm(t_color c1, t_color c2, t_color c3, t_color c4)
{
	t_color color;

	color.r = ((unsigned char)c1.r + (unsigned char)c2.r +
	(unsigned char)c3.r + (unsigned char)c4.r) / 4;
	color.g = ((unsigned char)c1.g + (unsigned char)c2.g +
	(unsigned char)c3.g + (unsigned char)c4.g) / 4;
	color.b = ((unsigned char)c1.b + (unsigned char)c2.b +
	(unsigned char)c3.b + (unsigned char)c4.b) / 4;
	return (color);
}
