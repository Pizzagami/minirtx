/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4dist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 14:10:01 by selgrabl          #+#    #+#             */
/*   Updated: 2019/12/20 05:23:33 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

float find_dist(t_vec origin, t_vec ray, t_tg shape)
{
    if (shape.type == 1)
        return(find_dist_sp(origin, ray, shape));
    if (shape.type == 2)
        return(find_dist_cy(origin, ray, shape));
    if (shape.type == 5)
        return(find_dist_ce(origin, ray, shape));
	return(find_dist_stp(origin, ray, shape));
}

int		between(t_vec vec, t_vec p1, t_vec p2, t_vec dot, int x)
{
	p2 = plus(fois(vec, p1.x - p2.x), p2);
	x = (plus(fois(vec, p1.x - dot.x), dot).y  >= p1.y &&
	plus(fois(vec, p1.x - dot.x), dot).y  <= p2.y)?  x : 1;
	return(x);
}
