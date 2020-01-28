/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raimbaultbrieuc <raimbaultbrieuc@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 18:10:42 by braimbau          #+#    #+#             */
/*   Updated: 2020/01/28 13:35:25 by raimbaultbr      ###   ########.fr       */
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
    if (fabs(chala) < 0.0001)
        return (init_vec(-b, 0, 0));
    else if (chala < 0)
        return (init_vec(0, 0, 0));
    else 
        return(init_vec(sqrtf(chala) - b, -sqrtf(chala) - b, 0));
}

t_vec   solver3(float coef0, float coef1, float coef2, float coef3)
{
    float po;
    float b;
    float c;
    float chala;
    float sub;

    sub = 1 / 3 * coef2 / coef3;
    po = pow(coef2 / coef3, 2);
    b = 1 / 3 * (-1 / 3 * po + coef1 / coef3);
    c = 1 / 2 * (2 / 27 * coef2 / coef3 * po - 1 / 3 * coef2 / coef3
        * coef1 / coef3 + coef0 / coef3);
    po = pow(b, 3);
    chala = c * c + po;
    if (fabs(chala) < 0.0001)
    {
        if(fabs(c) < 0.0001)
            return(init_vec(- sub, - sub, - sub));
        else
            return(init_vec(2 * cbrtf(-c), -cbrtf(-c) - sub, 0));
    }
    else if (chala < 0)
        return(init_vec(2 * sqrtf(-b) * cosf(1 / 3 * acosf (-c / sqrtf(-po)))- sub,
        -2 * sqrtf(-b) * cosf(1 / 3 * acosf (-c / sqrtf(-po)) + M_PI / 3) - sub,
         -2 * sqrtf(-b) * cosf(1 / 3 * acosf (-c / sqrtf(-po)) - M_PI / 3) - sub));
    else
        return(init_vec(cbrtf(sqrtf(chala) + c) + cbrtf(sqrtf(chala) - c)
        - sub ,0 ,0));
    
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
    if (fabs(d) < 0.0001)
        return(solver3(c, b, 0, 1)); // rajouter une col 0
    else
    {
        chala = solver3(1 / 2 * d * b  - 1 / 8 * c * c, -d, -0.5 * b, 1).x;
        po = pow(chala, 2) - d;
        chala = 2 * chala - b;
        if (fabs(po) < 0.0001)
            po = 0;
        else if (po > 0)
            po = sqrtf(po);
        else 
            return(init_vec(0,0,0));

    }
    return(init_vec(0,0,0));
}