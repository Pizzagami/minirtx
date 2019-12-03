/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 17:41:33 by selgrabl          #+#    #+#             */
/*   Updated: 2019/12/02 18:12:52 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

void	init_lst(int fd, t_rtx *rtx)
{
	t_tg	*shape;
	t_cam	*cam;
	t_light	*light;
	int x;

	x = 0;
	if (!(shape = malloc(sizeof(shape))))
		x = 1;
	shape->next = NULL;
	rtx->shape = shape;
	if (!(cam = malloc(sizeof(cam))))
		x = 1;
	cam->next = NULL;
	rtx->cam = cam;
	if (!(light = malloc(sizeof(light))))
		x = 1;
	light->next = NULL;
	rtx->light = light;
	if (x == 1)
	{
	write(2, "Error : allocation failed during init_lst\n", 42);
	close(fd);
	exit(1);
	}
}

t_tg	*last_tg(t_tg *lst)
{
	t_tg *current;

	current = lst;
	if (lst)
		while (lst && current->next)
			current = current->next;
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