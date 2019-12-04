/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 17:41:33 by selgrabl          #+#    #+#             */
/*   Updated: 2019/12/03 16:55:50 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

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
