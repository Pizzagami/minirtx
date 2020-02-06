/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 12:00:05 by selgrabl          #+#    #+#             */
/*   Updated: 2020/02/06 15:57:42 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

void	tri_vecs(t_tg *shape)
{
	t_vec tmp;

	if (shape->v1.z >= shape->vec.z)
	{
		tmp = shape->vec;
		shape->vec = shape->v1;
		shape->v1 = tmp;
	}
	if (shape->v2.z >= shape->vec.z)
	{
		tmp = shape->vec;
		shape->vec = shape->v2;
		shape->v2 = tmp;
	}
	if (shape->v2.x >= shape->v1.x)
	{
		tmp = shape->v1;
		shape->v1 = shape->v2;
		shape->v2 = tmp;
	}
}

float	dot(t_vec machin, t_vec bidule)
{
	return (machin.x * bidule.x + machin.y * bidule.y + machin.z * bidule.z);
}

t_vec	cross(t_vec machin, t_vec bidule)
{
	t_vec truc;

	truc.x = machin.y * bidule.z - machin.z * bidule.y;
	truc.y = machin.z * bidule.x - machin.x * bidule.z;
	truc.z = machin.x * bidule.y - machin.y * bidule.x;
	return (truc);
}

float	dist_dot(t_vec machin, t_vec bidule)
{
	return (sqrtf(pow(machin.x - bidule.x, 2) +
				pow(machin.y - bidule.y, 2) +
				pow(machin.z - bidule.z, 2)));
}
