/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 13:13:56 by selgrabl          #+#    #+#             */
/*   Updated: 2019/12/02 17:47:29 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

char	*check_color(char buf[BUFFER_SIZE], int *x, t_color *color, char *id)
{
	read_int(buf, x, &(color->r));
	if (color->r == -42)
		return (join("Error : Invalid integer for red of ", id));
	if (buf[(*x)++] != ',')
		return (join("Error : Invalid format for ", id));
	read_int(buf, x, &(color->g));
	if (color->g == -42)
		return (join("Error : Invalid integer for green of ", id));
	if (buf[(*x)++] != ',')
		return (join("Error : Invalid format for ", id));
	read_int(buf, x, &(color->b));
	if (color->b == - 42)
		return (join("Error : Invalid integer for blue of ", id));
	if (color->r > 255 || color->r < 0 || color->g > 255 ||
	color->g < 0 || color->b > 255 || color->b < 0)
		return (join("Error : Value(s) out of range for ", id));
	return (NULL);
}

char	*check_vec(char buf[BUFFER_SIZE], int *x, t_vec *vec, char *id)
{
	read_float(buf, x, &(vec->x));
	if (vec->x == NAF)
		return (join("Error : Invalid float for x of ", id));
	if (buf[(*x)++] != ',')
		return (join("Error : Invalid format for ", id));
	read_float(buf, x, &(vec->y));
	if (vec->y == NAF)
		return (join("Error : Invalid float for y of ", id));
	if (buf[(*x)++] != ',')
		return (join("Error : Invalid format for ", id));
	read_float(buf, x, &(vec->z));
	if (vec->z == NAF)
		return (join("Error : Invalid float for z of ", id));
	if (vec->x > 1 || vec->x < -1 || vec->y > 1 ||
	vec->y < -1 || vec->z > 1 || vec->z < -1)
		return (join("Error : Value(s) out of range for ", id));
	return (NULL);
}

char	*join(char *s1, char *s2)
{
	int		i;
	int		n;
	char	*r;

	if (ft_strlen(s1) + ft_strlen(s2) == 0)
		return (NULL);
	if (!(r = (char *)malloc((ft_strlen(s1) +ft_strlen(s2) + 1))))
		return (NULL);
	i = 0;
	n = 0;
	while (s1 != NULL && s1[i])
	{
		r[i] = s1[i];
		i++;
	}
	while (s2 != NULL && s2[n])
	{
		r[i + n] = s2[n];
		n++;
	}
	r[i + n] = 0;
	return (r);
}

char	*check_pos(char buf[BUFFER_SIZE], int *x, t_vec *vec, char *id)
{
	read_float(buf, x, &(vec->x));
	if (vec->x == NAF)
		return (join("Error : Invalid float for x of ", id));
	if (buf[(*x)++] != ',')
		return (join("Error : Invalid format for ", id));
	read_float(buf, x, &(vec->y));
	if (vec->y == NAF)
		return (join("Error : Invalid float for y of ", id));
	if (buf[(*x)++] != ',')
		return (join("Error : Invalid format for ", id));
	read_float(buf, x, &(vec->z));
	if (vec->z == NAF)
		return (join("Error : Invalid float for z of ", id));
	return (NULL);
}
