/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 12:06:54 by braimbau          #+#    #+#             */
/*   Updated: 2020/02/05 13:33:14 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

void	free_buf(char **buf)
{
	int i;

	i = 0;
	while (buf[i])
	{
		free(buf[i]);
		i++;
	}
	free(buf);
}

void	free_lists(t_cam *cam, t_light *light, t_tg *shape)
{
	t_cam	*tmpc;
	t_light	*tmplight;
	t_tg	*tmpshape;

	while (cam)
	{
		tmpc = cam;
		cam = cam->next;
		free(tmpc);
	}
	while (light)
	{
		tmplight = light;
		light = light->next;
		free(tmplight);
	}
	while (shape)
	{
		tmpshape = shape;
		shape = shape->next;
		free(tmpshape);
	}
}
