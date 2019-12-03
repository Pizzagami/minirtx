/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 13:13:56 by selgrabl          #+#    #+#             */
/*   Updated: 2019/12/03 15:47:10 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

char	*check_color(char buf[BUFFER_SIZE], int *x, t_color *color, char *id)
{
	color->r = read_int(buf, x);
	if (color->r == -42)
		return (join("Error : Invalid integer for red of ", id));
	if (buf[(*x)++] != ',')
		return (join("Error : Invalid format for ", id));
	color->g = read_int(buf, x);
	if (color->g == -42)
		return (join("Error : Invalid integer for green of ", id));
	if (buf[(*x)++] != ',')
		return (join("Error : Invalid format for ", id));
	color->b = read_int(buf, x);
	if (color->b == - 42)
		return (join("Error : Invalid integer for blue of ", id));
	if (color->r > 255 || color->r < 0 || color->g > 255 ||
	color->g < 0 || color->b > 255 || color->b < 0)
		return (join("Error : Value(s) out of range for ", id));
	return (NULL);
}

char	*check_vec(char buf[BUFFER_SIZE], int *x, t_vec *vec, char *id)
{
	vec->x = read_float(buf, x);
	if (vec->x == NAF)
		return (join("Error : Invalid float for x of ", id));
	if (buf[(*x)++] != ',')
		return (join("Error : Invalid format for ", id));
	vec->y = read_float(buf, x);
	if (vec->y == NAF)
		return (join("Error : Invalid float for y of ", id));
	if (buf[(*x)++] != ',')
		return (join("Error : Invalid format for ", id));
	vec->z = read_float(buf, x);
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
	vec->x = read_float(buf, x);
	if (vec->x == NAF)
		return (join("Error : Invalid float for x of ", id));
	if (buf[(*x)++] != ',')
		return (join("Error : Invalid format for ", id));
	vec->y = read_float(buf, x);
	if (vec->y == NAF)
		return (join("Error : Invalid float for y of ", id));
	if (buf[(*x)++] != ',')
		return (join("Error : Invalid format for ", id));
	vec->z = read_float(buf, x);
	if (vec->z == NAF)
		return (join("Error : Invalid float for z of ", id));
	return (NULL);
}
