/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4dist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 14:10:01 by selgrabl          #+#    #+#             */
/*   Updated: 2020/01/05 16:42:13 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

float       find_dist(t_vec origin, t_vec ray, t_tg shape)
{
    if (shape.type == 1)
        return(find_dist_sp(origin, ray, shape));
    if (shape.type == 2)
        return(find_dist_cy(origin, ray, shape));
    if (shape.type == 5)
        return(find_dist_ce(origin, ray, shape));
	return(find_dist_stp(origin, ray, shape));
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

float		find_dist_stcp(t_vec   origin, t_vec ray, t_tg shape)
{
    float x;

    x = (dot(ray, shape.vec) != 0) ?(dot(min(shape.center, origin),
        shape.vec)/ dot(ray, shape.vec)) : 0;
    if (shape.type == 5)
        x = (distce(shape, plus(origin, fois(ray, x))) == 1) ? x: 0;
    else if (shape.type == 4)
        x = (distsqr(shape, plus(origin, fois(ray, x))) == 1) ? x: 0;
    else if (shape.type == 3)
        x = (distri(shape, plus(origin, fois(ray, x))) == 1) ? x: 0;
    return((x > 0) ? x : -1.0);
}

float		find_dist_cy(t_vec   origin, t_vec ray, t_tg shape)
{
	origin.x = ray.x + shape.type;
	return(0.0);
}