/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 13:13:56 by selgrabl          #+#    #+#             */
/*   Updated: 2019/12/04 13:16:38 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

char	*read_color(char buf[BUFFER_SIZE], int *x, t_color *color, char *id)
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

char	*read_vec(char buf[BUFFER_SIZE], int *x, t_vec *vec, char *id)
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

char	*read_pos(char buf[BUFFER_SIZE], int *x, t_vec *vec, char *id)
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

void	init_lst(int fd, t_rtx *rtx)
{
	t_tg	*shape;
	t_light *light;
	t_cam	*cam;

	shape = malloc(sizeof(t_tg));
	rtx->shape = shape;
	rtx->shape->next = NULL;
	light = malloc(sizeof(t_light));
	rtx->light = light;
	rtx->light->next = NULL;
	cam = malloc(sizeof(t_cam));
	rtx->cam = cam;
	rtx->cam->next = NULL;
}


int	ft_strcmp(char *s1, char *s2)
{
	unsigned int i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - s2[i]);
		i++;
	}
	if (((s1[i] == '\0' && s2[i] != '\0') ||
				(s2[i] == '\0' && s1[i] != '\0')))
		return ((unsigned char)s1[i] - s2[i]);
	return (0);
}
