/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4aa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 10:38:58 by braimbau          #+#    #+#             */
/*   Updated: 2020/01/13 19:00:37 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

void    anti_aliesing(t_res res, char **id)
{
	int     x;
	int     y;

	x = 0;
	while (x < res.x)
	{
		y = 0;
		while (y < res.y)
		{
			if (x && y && x != res.x - 1 && y != res.y - 1)
			{
			(*id)[(x + (y * res.x)) * 4] /= 2;//(char) (*id)[(x + (y * res.x)) * 4]/2;
			(*id)[((x + (y * res.x)) * 4) + 1] /= 2;//(char) (*id)[((x + (y * res.x)) * 4) + 1]/2;
			(*id)[((x + (y * res.x)) * 4 )+ 2] /= 2;//(char) (*id)[((x + (y * res.x)) * 4 )+ 2]/2;
			}
			else
			(*id)[(x + (y * res.x)) * 4] = (*id)[(x + (y * res.x)) * 4];
			(*id)[((x + (y * res.x)) * 4) + 1] = (*id)[((x + (y * res.x)) * 4) + 1];
			(*id)[((x + (y * res.x)) * 4 )+ 2] = (*id)[((x + (y * res.x)) * 4 )+ 2];
			y++;
		}
		x++;
	}
}

void    filter(char filter, t_res res, char **id)
{
	int     x;
	int     y;
	int		m;

	if (filter == 0)
		return;
	x = 0;
	while (x < res.x)
	{
		y = 0;
		while (y < res.y)
		{
			if (filter == 'G' || filter == 'R' || filter == 'Y' || filter == 'l')
				(*id)[(x + (y * res.x)) * 4] = 0;//b
			if (filter == 'B' || filter == 'R' || filter == 'P' || filter == 'l')
				(*id)[((x + (y * res.x)) * 4) + 1] = 0; //g
			if (filter == 'B' || filter == 'G' || filter == 'C' || filter == 'r')
				(*id)[((x + (y * res.x)) * 4 )+ 2] = 0; //r
			if (filter == 'W')
			{
				m = ((*id)[(x + (y * res.x)) * 4] + (*id)[((x + (y * res.x)) * 4) + 1] + (*id)[((x + (y * res.x)) * 4 )+ 2])/3;
				(*id)[(x + (y * res.x)) * 4] = m;//b
				(*id)[((x + (y * res.x)) * 4) + 1] = m; //g
				(*id)[((x + (y * res.x)) * 4 )+ 2] = m; //r
			}
			if (filter == 'N')
			{
				(*id)[(x + (y * res.x)) * 4] *= -1;//b
				(*id)[((x + (y * res.x)) * 4) + 1] *= -1; //g
				(*id)[((x + (y * res.x)) * 4 )+ 2] *= -1; //r
			}
			y++;
		}
		x++;
	}
}

void	make_3d(t_cam **cam, t_res res)
{
	t_cam *ca;
	int	x;
	int y;

	ca = *cam;
	while(ca)
	{
		if (ca->filter == 'r')
		{
			x = 0;
			while (x < res.x)
			{
				y = 0;
				while (y < res.y)
				{
					ca->id[(x + (y * res.x)) * 4 + 2] = ca->next->id[(x + (y * res.x)) * 4 + 2];  //r
					y++;
				}
				x++;
			}		
		}
		ca = ca->next;
	}
}