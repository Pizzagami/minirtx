/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 17:26:19 by braimbau          #+#    #+#             */
/*   Updated: 2020/01/15 14:56:06 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

char	*read_float(char *str, float *value, char *id, float max)
{
	*value = ft_atof(str);
	if (isnan(*value))
		return(join("invalid value for ", id));
	if (*value < 0)
		return(join("Value out of range for ", id));
	if (max > 0 && *value > max)
		return(join("Value out of range for ", id));
	return (NULL);
}

void	create_tri(t_vec p1, t_vec p2, t_vec p3, t_rtx *rtx)
{
	t_tg *shape;
	t_tg tmp;

	tmp = *(rtx->shape);
	shape = malloc(sizeof(t_tg));
	shape->next = rtx->shape;
	rtx->shape = shape;
	rtx->shape->type = 3;
	rtx->shape->trans = tmp.trans;
	rtx->shape->refl = tmp.refl;
	rtx->shape->color = tmp.color;
	rtx->shape->p1 = p1;
	rtx->shape->p2 = p2;
	rtx->shape->p3 = p3;
	shape->vec = normalize(cross(min(shape->p2, shape->p1),
		min(shape->p3, shape->p1)));
	shape->center = shape->p1;
}

void	export_to_bmp(char *id, t_res res)
{
	int fd;

	(void)id;
	fd = 42;
	(void)res;
	printf("test\n");
//	fd = open("./file", O_CREAT  O_WRONLY), 777);
	write(fd, "BM", 24);
}