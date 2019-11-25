/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 12:17:38 by selgrabl          #+#    #+#             */
/*   Updated: 2019/11/25 12:47:52 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

int second_degre(float a, float b, float c, float *x1, float *x2)
{
    float d;

    if (a == 0)
    {
        *x1 = - c / b;
        return (1);
    }
    d = pow(b, 2) - 4 * a * c;
    printf("|%f|\n", d);
    if (d < 0)
        return (0);
    else if (d == 0)
    {
        *x1 = -b / (2 * a);
        return (1);
    }
    else
    {
        *x1 = (-b + sqrt(d)) / (2 * a);
        *x2 = (-b - sqrt(d)) / (2 * a);
        return (2);
    }
}

float dot(t_vec machin, t_vec bidule)
{
	return(machin.x * bidule.x + machin.y * bidule.y + machin.z * bidule.z);
}