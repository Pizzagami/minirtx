/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 09:27:03 by selgrabl          #+#    #+#             */
/*   Updated: 2020/02/06 15:57:09 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

static void	make_filter_n(char **id, t_res res, int x, int y)
{
	(*id)[(x + (y * res.x)) * 4] = 255 - (*id)[(x + (y * res.x)) * 4];
	(*id)[((x + (y * res.x)) * 4) + 1] = 255 -
	(*id)[((x + (y * res.x)) * 4) + 1];
	(*id)[((x + (y * res.x)) * 4) + 2] = 255 -
	(*id)[((x + (y * res.x)) * 4) + 2];
}

void		filter(char f, t_res res, char **id)
{
	int	x;
	int	y;

	if (f == 0)
		return ;
	x = 0;
	while (x < res.x)
	{
		y = 0;
		while (y < res.y)
		{
			if (f == 'G' || f == 'R' || f == 'Y' || f == 'l')
				(*id)[(x + (y * res.x)) * 4] = 0;
			if (f == 'B' || f == 'R' || f == 'P' || f == 'l')
				(*id)[((x + (y * res.x)) * 4) + 1] = 0;
			if (f == 'B' || f == 'G' || f == 'C' || f == 'r')
				(*id)[((x + (y * res.x)) * 4) + 2] = 0;
			if (f == 'N')
				make_filter_n(id, res, x, y);
			y++;
		}
		x++;
	}
}

static void	delete_cam(t_cam *ca)
{
	t_cam *tmp;

	tmp = ca->next;
	ca->next = ca->next->next;
	free(tmp);
}

void		make_3d(t_cam **cam, t_res res)
{
	t_cam	*ca;
	int		x;
	int		y;

	ca = *cam;
	while (ca)
	{
		if (ca->filter == 'r')
		{
			x = 0;
			while (x < res.x)
			{
				y = 0;
				while (y < res.y)
				{
					ca->id[(x + (y * res.x)) * 4 + 2] =
					ca->next->id[(x + (y * res.x)) * 4 + 2];
					y++;
				}
				x++;
			}
			delete_cam(ca);
		}
		ca = ca->next;
	}
}
