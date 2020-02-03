/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_basics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raimbaultbrieuc <raimbaultbrieuc@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 19:18:20 by braimbau          #+#    #+#             */
/*   Updated: 2020/02/03 14:17:28 by raimbaultbr      ###   ########.fr       */
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
	return (vec);
}

float	length(t_vec vec)
{
	return(sqrtf(dot(vec, vec)));
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

t_vec	init_vec(float x, float y, float z)
{
	t_vec vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}
