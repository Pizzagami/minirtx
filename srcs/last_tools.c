/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 17:41:33 by selgrabl          #+#    #+#             */
/*   Updated: 2019/12/03 15:41:52 by braimbau         ###   ########.fr       */
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

t_tg	*last_tg(t_tg *lst)
{
	t_tg *current;

	current = lst;
	if (lst)
		while (lst && current->next)
			{
				current = current->next;
				printf("test\n");
			}
	printf("LOL\n");
	return (current);
}

t_cam	*last_cam(t_cam *lst)
{
	t_cam *current;

	current = lst;
	if (lst)
		while (lst && current->next)
			current = current->next;
	return (current);
}

t_light	*last_light(t_light *lst)
{
	t_light *current;

	current = lst;
	if (lst)
		while (lst && current->next)
			current = current->next;
	return (current);
}