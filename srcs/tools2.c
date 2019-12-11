/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 13:13:56 by selgrabl          #+#    #+#             */
/*   Updated: 2019/12/11 10:50:25 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

char	*read_color(char *str, t_color *color, char *id)
{
	char **buf;

	buf = ft_split(str, ",");
	if (!buf[0] || !buf[1] || !buf[2] || buf[3] != NULL)
		return (join("Invalid format for color ", id));
	color->r = ft_atoi(buf[0]);
	if (color->r == -42)
		return (join("Invalid integer for red of ", id));
	color->g = ft_atoi(buf[1]);
	if (color->g == -42)
		return (join("Invalid integer for green of ", id));
	color->b = ft_atoi(buf[2]);
	if(color->b == -42)
		return (join("Invalid integer for blue of ", id));
	if (color->r > 255 || color->r < 0 || color->g > 255 ||
	color->g < 0 || color->b > 255 || color->b < 0)
		return (join("Value(s) out of range for ", id));
	if (str[ft_strlen(str) - 1] < '0' || str[ft_strlen(str) - 1] > '9')
		return (join("Invalid format for color ", id));
	return (NULL);
}

char	*read_vec(char *str, t_vec *vec, char *id)
{
	char **buf;

	buf = ft_split(str, ",");
	if (!buf[0] || !buf[1] || !buf[2] || buf[3] != NULL)
		return (join("Invalid format for vector ", id));
	 vec->x = ft_atof(buf[0]);
	if (isnan(vec->x))
		return (join("Invalid float for red of ", id));
	vec->y = ft_atoi(buf[1]);
	if (isnan(vec->y))
		return (join("Invalid float for green of ", id));
	vec->z = ft_atof(buf[2]);
	if(isnan(vec->z))
		return (join("Invalid float for blue of ", id));
	if (vec->x > 1 || vec->x < -1 || vec->y > 1 ||
	vec->y < -1 || vec->z > 1 || vec->z < -1)
		return (join("Value(s) out of range for ", id));
	if (str[ft_strlen(str) - 1] < '0' || str[ft_strlen(str) - 1] > '9')
		return (join("Invalid format for vector ", id));
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

char	*read_pos(char *str, t_vec *vec, char *id)
{
	char **buf;

	buf = ft_split(str, ",");
	if (!buf[0] || !buf[1] || !buf[2] || buf[3] != NULL)
		return (join("Invalid format for position ", id));
	 vec->x = ft_atof(buf[0]);
	if (isnan(vec->x))
		return (join("Invalid float for x of ", id));
	vec->y = ft_atoi(buf[1]);
	if (isnan(vec->y))
		return (join("Invalid float for y of ", id));
	vec->z = ft_atof(buf[2]);
	if(isnan(vec->z))
		return (join("Invalid float for z of ", id));
	if (str[ft_strlen(str) - 1] < '0' || str[ft_strlen(str) - 1] > '9')
		return (join("Invalid format for position ", id));
	return (NULL);
}

void	init_lst(int fd, t_rtx *rtx)
{
	t_tg	*shape;
	t_light *light;
	t_cam	*cam;

	rtx->shape = NULL;
	rtx->cam = NULL;
	rtx->light = NULL;
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
