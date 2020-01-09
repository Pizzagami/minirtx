/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4lite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 17:21:07 by braimbau          #+#    #+#             */
/*   Updated: 2020/01/08 17:16:09 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

float	cal_lite_inter(t_rtx rtx, t_light *li, t_vec point, t_tg shape)
{
	t_tg	*sh;
	float	ldist;
	float	c;

	sh = rtx.shape;
	c = 1;

	ldist = find_dist(li->pos, min(point, li->pos), &shape);
	while (sh)
	{
		if (find_dist(li->pos, min(point, li->pos), sh) < ldist &&
		find_dist(li->pos, min(point, li->pos), sh) > 0)
		{
			c *= sh->trans;
		}
		sh = sh->next;
	}
	return (c);
}