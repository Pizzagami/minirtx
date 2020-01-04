/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 19:17:07 by braimbau          #+#    #+#             */
/*   Updated: 2019/12/19 19:10:01 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

t_color	color_init(int r, int g, int b)
{
	t_color color;

	color.r = r;
	color.g = g;
	color.b = b;
	return(color);
}

t_color lfois(t_color color, float a)
{
    color.r *= a;
    color.g *= a;
    color.b *= a;
    return (color);
}

t_color color_cap(t_color color, t_color max)
{
   if (color.r > max.r)
       color.r = max.r;
   if (color.g > max.g)
       color.g = max.g;
   if (color.b > max.b)
       color.b = max.b;
   return (color);
}

t_color color_add(t_color base, t_color add, float coef)
{
   base.r += add.r * coef;
   base.g += add.g * coef;
   base.b += add.b * coef;
   return (base);
}

t_color cosha(float ratio, t_color light, t_color shape)
{
    t_color color;
		color.r = ratio * light.r / 255 * shape.r;
		color.g = ratio * light.g / 255 * shape.g;
		color.b = ratio * light.b / 255 * shape.b;
    return(color);
}