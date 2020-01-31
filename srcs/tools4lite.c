/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4lite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 17:21:07 by braimbau          #+#    #+#             */
/*   Updated: 2020/01/31 11:15:56 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

float	cal_lite_inter(t_rtx rtx, t_light *li, t_vec point, t_tg shape)
{
	t_tg	*sh;
	float	ldist;
	float	c;
	float	dist;

	sh = rtx.shape;
	c = 1;
	if (li->para.x || li->para.y || li->para.z)
	{
		while (sh)
		{
			dist = find_dist(point, fois(li->para, -1), sh);
			if (dist != -1 && dist > 0.01)
				c *= sh->trans;
			sh = sh->next;
		}
	}
	else
	{
		ldist = find_dist(li->pos, normalize(min(li->pos, point)), &shape);
		while (sh)
		{
			dist = find_dist(point, normalize(min(li->pos, point)), sh);
			if (dist < ldist && dist > 0)
			{
				c *= sh->trans;
			}
			sh = sh->next;
		}
	}
	return (c);

}