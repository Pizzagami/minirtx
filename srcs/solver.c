/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 18:10:42 by braimbau          #+#    #+#             */
/*   Updated: 2020/01/27 19:40:07 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

t_vec   solver2(float coef[5])
{
    float b;
    float c;
    float chala;

    b = coef[1] / (2 * coef[2]);
    c = coef[0] / coef[2];
    chala = b * b - c;
    if (chala == 0)
        return (init_vec(-b, 0, 0));
    else if (chala < 0)
        return (init_vec(0, 0, 0));
    else 
        return(init_vec(sqrtf(chala) - b, -sqrtf(chala) - b, 0));
}

t_vec   solver3(float coef[5])
{
    float po;
    float b;
    float c;
    float chala;

    coef[4] = 1 / 3 * coef[2] / coef[3];
    po = pow(coef[2] / coef[3], 2);
    b = 1 / 3 * (-1 / 3 * po + coef[1] / coef[3]);
    c = 1 / 2 * (2 / 27 * coef[2] / coef[3] * po - 1 / 3 * coef[2] / coef[3]
        * coef[1] / coef[3] + coef[0] / coef[3]);
    po = pow(b, 3);
    chala = c * c + po;
    if (chala == 0)
    {
        if(c == 0)
            return(init_vec(- coef[4], - coef[4], - coef[4]));
        else
            return(init_vec(2 * cbrtf(-c), -cbrtf(-c) - coef[4], 0));
    }
    else if (chala < 0)
        return(init_vec(2 * sqrtf(-b) * cosf(1 / 3 * acosf (-c / sqrtf(-po)))- coef[4],
        -2 * sqrtf(-b) * cosf(1 / 3 * acosf (-c / sqrtf(-po)) + M_PI / 3) - coef[4],
         -2 * sqrtf(-b) * cosf(1 / 3 * acosf (-c / sqrtf(-po)) - M_PI / 3) - coef[4]));
    else
        return(init_vec(cbrtf(sqrtf(chala) + c) + brtf(sqrtf(chala) - c)
        - coef[4] ,0 ,0));
    
}

t_vec   solver4(float coef[5])
{
    
    float po;
    float b;
    float c;
    float d;
    float chala;

    po = pow(coef[3] / coef[4], 2);
    b = -3 / 8 * po + coef[2] / coef[4];
    c = 1 / 8 * po * coef[3] / coef[4] - 1 / 2 * coef[3] / coef[4] * coef[2] /
    coef[4] + coef[1] / coef[4];
    d = -3 / 256 * po * po + 1 / 16 * po * coef[2] / coef[4] - 1 / 4 *
    coef[3] / coef[4] * coef[1] / coef[4] + coef[0] / coef[4];
    if (d == 0)
        //c la merde
    return(init_vec(0,0,0))
}