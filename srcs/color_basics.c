/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_basics.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 19:17:07 by braimbau          #+#    #+#             */
/*   Updated: 2020/02/01 11:36:06 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

t_color	color_init(int r, int g, int b)
{
	t_color color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

t_color	lfois(t_color color, float a)
{
	color.r *= a;
	color.g *= a;
	color.b *= a;
	return (color);
}

t_color	color_cap(t_color color, t_color max)
{
	if (color.r > max.r)
		color.r = max.r;
	if (color.g > max.g)
		color.g = max.g;
	if (color.b > max.b)
		color.b = max.b;
	return (color);
}

t_color	color_add(t_color base, t_color add, float coef)
{
	base.r += add.r * coef;
	base.g += add.g * coef;
	base.b += add.b * coef;
	return (base);
}
