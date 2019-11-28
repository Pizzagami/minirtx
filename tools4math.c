/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 12:17:38 by selgrabl          #+#    #+#             */
/*   Updated: 2019/11/28 19:32:39 by selgrabl         ###   ########.fr       */
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

t_vec normalize(t_vec vect)
{
	t_vec tmp;

	tmp = vect;
	vect.x = vect.x / sqrtf(dot(tmp, tmp));
	vect.y = vect.y / sqrtf(dot(tmp, tmp));
	vect.z = vect.z / sqrtf(dot(tmp, tmp));
	return(vect);
}

t_vec	min(t_vec truc, t_vec machin)
{
	truc.x -= machin.x;
	truc.y -= machin.y;
	truc.z -= machin.z;
	return (truc);
}

float	dot(t_vec machin, t_vec bidule)
{
	return(machin.x * bidule.x + machin.y * bidule.y + machin.z * bidule.z);
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

int ft_atoi(char *str)
{
	int i;
	int nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			nb = nb * 10 + str[i] - 48;
		i++;
	}
	return (nb);
}

float find_dist_s(t_vec ray, t_vec origin, t_vec center, int r)
{
	float x1;


	float x2;
	int s;
	int mlp;

	s = second_degre(dot(ray, ray), 2 * dot(ray, min(origin, center)), dot(min(origin, center), min(origin, center)) - pow(r, 2), &x1, &x2);
	if (s == 1 && x1 > 0)
		return (x1);
	else if (s == 2 && (x1 > 0 && x2 > 0))
	{
		if (x2 > 0)
			return ((x1 <= x2 && x1 > 0) ? x1 : x2);
		return (x1);
	}
	return (-1);
}