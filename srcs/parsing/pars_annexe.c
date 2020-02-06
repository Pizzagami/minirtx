/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_annexe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:28:58 by selgrabl          #+#    #+#             */
/*   Updated: 2020/02/06 15:57:47 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

char		*pars_aa(char **buf, t_rtx *rtx)
{
	(void)buf;
	rtx->aa = 2;
	return (NULL);
}

void		init_trd(t_tg *shape)
{
	shape->trans = 0;
	shape->refl = 0;
	shape->dam = 0;
}

void		vec_tri(t_tg *shape)
{
	shape->vec = normalize(shape->vec);
	find_vecs(shape);
	corners(shape);
	shape->vec = normalize(cross(min(shape->p2, shape->p1),
	min(shape->p3, shape->p1)));
	shape->normal = shape->vec;
}

void		face_py(t_tg *shape, t_rtx *rtx)
{
	t_vec x;

	x = plus(shape->center, fois(shape->vec, shape->dia));
	create_tri(x, shape->p1, shape->p2, rtx);
	create_tri(x, shape->p2, shape->p3, rtx);
	create_tri(x, shape->p3, shape->p4, rtx);
	create_tri(x, shape->p4, shape->p1, rtx);
}
