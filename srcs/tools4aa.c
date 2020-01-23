/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4aa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 10:38:58 by braimbau          #+#    #+#             */
/*   Updated: 2020/01/19 16:42:08 by braimbau         ###   ########.fr       */
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
	float		m;

	if (filter == 0)
		return;
	x = 0;
	while (x < res.x)
	{
		y = 0;
		while (y < res.y)
		{
			if (filter == 'S')
			{

			}
			if (filter == 'G' || filter == 'R' || filter == 'Y' || filter == 'l')
				(*id)[(x + (y * res.x)) * 4] = 0;//b
			if (filter == 'B' || filter == 'R' || filter == 'P' || filter == 'l')
				(*id)[((x + (y * res.x)) * 4) + 1] = 0; //g
			if (filter == 'B' || filter == 'G' || filter == 'C' || filter == 'r')
				(*id)[((x + (y * res.x)) * 4 )+ 2] = 0; //r
			if (filter == 'W')
			{
				m = 0.0722 * (int)(127 + ((*id)[(x + (y * res.x)) * 4]) + 0.7152 * (127 + (int)(*id)[((x + (y * res.x))) * 4 + 1]) + 0.2126 * (127 + (int)(*id)[((x + (y * res.x)) * 4 )+ 2]));
				(*id)[(x + (y * res.x)) * 4] = m - 127;//b
				(*id)[((x + (y * res.x)) * 4) + 1] = m - 127; //g
				(*id)[((x + (y * res.x)) * 4 )+ 2] = m - 127; //r
			}
			if (filter == 'N')
			{
				(*id)[(x + (y * res.x)) * 4] = 255 - (*id)[(x + (y * res.x)) * 4]; //b
				(*id)[((x + (y * res.x)) * 4) + 1] = 255 - (*id)[((x + (y * res.x)) * 4) + 1]; //g
				(*id)[((x + (y * res.x)) * 4 )+ 2] = 255 - (*id)[((x + (y * res.x)) * 4 )+ 2]; //r
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