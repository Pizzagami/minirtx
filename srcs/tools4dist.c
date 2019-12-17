/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4dist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 14:10:01 by selgrabl          #+#    #+#             */
/*   Updated: 2019/12/17 17:01:32 by selgrabl         ###   ########.fr       */
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

int		between(t_vec vec, t_vec p1, t_vec p2, t_vec dot)
{
	int		x;
	float	r;

	r = vec.y / vec.x;
	x = (dot.x / r <= p2.x / r && dot.x / r >= p1.x / r) ? 0 : 1;
	return(x);
}