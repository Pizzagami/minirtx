/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 18:10:42 by braimbau          #+#    #+#             */
/*   Updated: 2020/01/28 16:48:10 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

t_tor   solver2(float coef0, float coef1, float coef2)
{
    float b;
    float c;
    float chala;

    b = coef1 / (2 * coef2);
    c = coef0 / coef2;
    chala = b * b - c;
    if (fabs(chala) < 0.0001)
        return(init_tor(1, -b, 0, 0, 0));
    else if (chala < 0)
        return(init_tor(0, 0, 0, 0, 0));
    else 
        return(init_tor(2, sqrtf(chala) - b, -sqrtf(chala) - b, 0, 0));
}

t_tor   solver3(float coef0, float coef1, float coef2, float coef3)
{
    float po;
    float b;
    float c;
    float chala;
    float sub;

    sub = coef2 / coef3 / 3;
    po = pow(coef2 / coef3, 2);
    b = 1 / 3 * (-1 / 3 * po + coef1 / coef3);
    c = 1 / 2 * (2 / 27 * coef2 / coef3 * po - 1 / 3 * coef2 / coef3
        * coef1 / coef3 + coef0 / coef3);
    po = pow(b, 3);
    chala = c * c + po;
    if (fabs(chala) < 0.0001)
    {
        if(fabs(c) < 0.0001)
            return(init_tor(3, - sub, - sub, - sub, 0));
        else
            return(init_tor(2, 2 * cbrtf(-c), -cbrtf(-c) - sub, 0, 0));
    }
    else if (chala < 0)
        return(init_tor(3, 2 * sqrtf(-b) * cosf(1 / 3 * acosf (-c / sqrtf(-po))) - sub,
       -2 * sqrtf(-b) * cosf(1 / 3 * acosf (-c / sqrtf(-po)) + M_PI / 3) - sub,
       -2 * sqrtf(-b) * cosf(1 / 3 * acosf (-c / sqrtf(-po)) - M_PI / 3) - sub, 0));
    else
        return(init_tor(1, cbrtf(sqrtf(chala) + c) + cbrtf(sqrtf(chala) - c)
        - sub , 0, 0, 0));
    
}

t_tor   solver4(float coef[5])
{
    
    float po;
    float b;
    float c;
    float d;
    float chala;
    float z;

    po = pow(coef[3] / coef[4], 2);
    b = -3 / 8 * po + coef[2] / coef[4];
    c = 1 / 8 * po * coef[3] / coef[4] - 1 / 2 * coef[3] / coef[4] * coef[2] /
    coef[4] + coef[1] / coef[4];
    d = -3 / 256 * po * po + 1 / 16 * po * coef[2] / coef[4] - 1 / 4 *
    coef[3] / coef[4] * coef[1] / coef[4] + coef[0] / coef[4];
    if (fabs(d) < 0.0001)
        return(solver3(c, b, 0, 1));
    else
    {
        z = solver3(1 / 2 * d * b  - 1 / 8 * c * c, -d, -0.5 * b, 1).s0;
		//printf("%f\n", z);
        po = pow(z, 2) - d;
        chala = 2 * z- b;
        if (fabs(po) < 0.0001)
            po = 0;
        else if (po > 0)
            po = sqrtf(po);
        else 
            return(init_tor(0, 0, 0, 0, 0));
        if (fabs(chala) < 0.0001)
            chala = 0;
        else if (chala > 0)
            chala = sqrtf(chala);
        else 
            return(init_tor(0, 0, 0, 0, 0));
		printf("ggg\n");
        return(init_tor(4, solver2(z - po, (c < 0) ? -chala: chala, 1).s0, solver2(z -
        po, (c < 0) ? -chala: chala, 1).s1, solver2(z + po, (c < 0) ? -chala:
        chala, 1).s0, solver2(z + po, (c < 0) ? -chala: chala, 1).s1));
	}
	return(init_tor(0,0,0,0,0));
}

float   dist_tor(float coef[5])
{
    float a;
    t_tor root;

    a = 1 / 4 * coef[3] / coef[4];
    root = solver4(coef);

    if(root.nb == 0)
        return (-1.0);
    root.s0 -= a; 
	root.s1 -= a;
	root.s2 -= a;
	root.s3 -= a;
	root.s0 = (root.s0 > root.s1 && root.nb >= 2) ? root.s1: root.s0;
	root.s0 = (root.s0 > root.s2 && root.nb >= 3) ? root.s2: root.s0;
	root.s0 = (root.s0 > root.s3 && root.nb >= 4) ? root.s3: root.s0;
	//printf("%f\n", root.s0);
	return(root.s0);
}