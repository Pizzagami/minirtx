/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4vector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 19:18:20 by braimbau          #+#    #+#             */
/*   Updated: 2020/01/13 18:16:20 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

t_vec	normalize(t_vec vec)
{
	t_vec tmp;

	tmp = vec;
	vec.x /= sqrtf(dot(tmp, tmp));
	vec.y /= sqrtf(dot(tmp, tmp));
	vec.z /= sqrtf(dot(tmp, tmp));
	return(vec);
}

t_vec	min(t_vec truc, t_vec machin)
{
	truc.x -= machin.x;
	truc.y -= machin.y;
	truc.z -= machin.z;

	return (truc);
}

t_vec	plus(t_vec truc, t_vec machin)
{
	truc.x += machin.x;
	truc.y += machin.y;
	truc.z += machin.z;
	return (truc);
}

t_vec	fois(t_vec truc, float a)
{
	truc.x *= a;
	truc.y *= a;
	truc.z *= a;
	return (truc);
}

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