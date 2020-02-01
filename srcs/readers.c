/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 10:05:12 by braimbau          #+#    #+#             */
/*   Updated: 2020/02/01 11:55:28 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

char	*read_color(char *str, t_color *color, char *id)
{
	char **buf;

	buf = ft_split(str, ",");
	if (!buf[0] || !buf[1] || !buf[2] || buf[3] != NULL)
		return (join("Invalid format for color", id));
	color->r = ft_atoi(buf[0]);
	if (color->r == -42)
		return (join("Invalid integer for color red", id));
	color->g = ft_atoi(buf[1]);
	if (color->g == -42)
		return (join("Invalid integer for color green", id));
	color->b = ft_atoi(buf[2]);
	if (color->b == -42)
		return (join("Invalid integer for color blue", id));
	if (color->r > 255 || color->r < 0 || color->g > 255 ||
	color->g < 0 || color->b > 255 || color->b < 0)
		return (join("Value(s) out of range for color", id));
	if (str[ft_strlen(str) - 1] < '0' || str[ft_strlen(str) - 1] > '9')
		return (join("Invalid format for color ", id));
	return (NULL);
}

char	*read_vec(char *str, t_vec *vec, char *id)
{
	char **buf;

	buf = ft_split(str, ",");
	if (!buf[0] || !buf[1] || !buf[2] || buf[3] != NULL)
		return (join("Invalid format for vector", id));
	vec->x = ft_atof(buf[0]);
	if (isnan(vec->x))
		return (join("Invalid float for vector x", id));
	vec->y = ft_atof(buf[1]);
	if (isnan(vec->y))
		return (join("Invalid float for vector y", id));
	vec->z = ft_atof(buf[2]);
	if (isnan(vec->z))
		return (join("Invalid float for vector z", id));
	if (vec->x > 1 || vec->x < -1 || vec->y > 1 ||
	vec->y < -1 || vec->z > 1 || vec->z < -1)
		return (join("Value(s) out of range for vector", id));
	if (str[ft_strlen(str) - 1] < '0' || str[ft_strlen(str) - 1] > '9')
		return (join("Invalid format for color ", id));
	return (NULL);
}

char	*read_pos(char *str, t_vec *vec, char *id)
{
	char **buf;

	buf = ft_split(str, ",");
	if (!buf[0] || !buf[1] || !buf[2] || buf[3] != NULL)
		return (join("Invalid format for position", id));
	vec->x = ft_atof(buf[0]);
	if (isnan(vec->x))
		return (join("Invalid float for position x", id));
	vec->y = ft_atof(buf[1]);
	if (isnan(vec->y))
		return (join("Invalid float for position y", id));
	vec->z = ft_atof(buf[2]);
	if (isnan(vec->z))
		return (join("Invalid float for position z", id));
	if (str[ft_strlen(str) - 1] < '0' || str[ft_strlen(str) - 1] > '9')
		return (join("Invalid format for position ", id));
	return (NULL);
}

char	*read_float(char *str, float *value, char *id, float max)
{
	*value = ft_atof(str);
	if (isnan(*value))
		return (join("invalid value for ", id));
	if (*value < 0)
		return (join("Value out of range for ", id));
	if (max > 0 && *value > max)
		return (join("Value out of range for ", id));
	return (NULL);
}
