/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4vector2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 19:19:08 by braimbau          #+#    #+#             */
/*   Updated: 2019/12/08 14:00:18 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

float	dot(t_vec machin, t_vec bidule)
{
	return(machin.x * bidule.x + machin.y * bidule.y + machin.z * bidule.z);
}

t_vec   cross(t_vec machin, t_vec bidule)
{
    t_vec truc;

    truc.x = machin.y * bidule.z - machin.z * bidule.y;
    truc.y = machin.z * bidule.x - machin.x * bidule.z;
    truc.z = machin.x * bidule.y - machin.y * bidule.x;
	return(truc);
}