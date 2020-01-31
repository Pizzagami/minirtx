/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools4aa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raimbaultbrieuc <raimbaultbrieuc@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 10:38:58 by braimbau          #+#    #+#             */
/*   Updated: 2020/01/28 14:30:10 by raimbaultbr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

static void	apply_aa(t_rtx *rtx, t_cam *cam, char **id)
{
	int		x;
	int		y;
	t_color	color;

	x = 0;
	while (x < rtx->res.x)
	{
		y = 0;
		while (y < rtx->res.y)
		{
			rtx->res.x *= rtx->aa;
			color = cm(cp(x * 2, y * 2, cam->id, rtx->res), cp(x * 2 + 1, y * 2,
			cam->id, rtx->res), cp(x * 2 + 1, y * 2 + 1, cam->id, rtx->res),
			cp(x * 2, y * 2 + 1, cam->id, rtx->res));
			rtx->res.x /= rtx->aa;
			mlx_put_pixel_img(x, y, id, rtx->res.x, color);
			y++;
		}
		x++;
	}
}

static void	apply_lq(t_rtx *rtx, t_cam *cam, char **id)
{
	int		x;
	int		y;
	t_color	color;

	x = 0;
	while (x < rtx->res.x)
	{
		y = 0;
		while (y < rtx->res.y)
		{
				rtx->res.x /= 1 / rtx->aa;
				color = cp(x / (1 / rtx->aa), y / (1 / rtx->aa),
				cam->id, rtx->res);
				rtx->res.x *= 1 / rtx->aa;
			mlx_put_pixel_img(x, y, id, rtx->res.x, color);
			y++;
		}
		x++;
	}
}

void		anti_aliesing(t_cam *cam, t_rtx *rtx)
{
	int		x;
	void	*img_ptr;
	char	*id;

	if (rtx->aa == 1)
		return;
	rtx->res.x /= rtx->aa;
	rtx->res.y /= rtx->aa;
	img_ptr = mlx_new_image(rtx->mlx_ptr, rtx->res.x, rtx->res.y);
	id = mlx_get_data_addr(img_ptr, &x, &x, &x);
	if (rtx->aa > 1)
		apply_aa(rtx, cam, &id);
	else if (rtx->aa < 1)
		apply_lq(rtx, cam, &id);
	cam->id = id;
	cam->img = img_ptr;
}

void	filter(char filter, t_res res, char **id)
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
	t_cam *tmp;
	int	x;
	int y;
	(void)res;
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
			tmp = ca->next;
			ca->next = ca->next->next;
			free(tmp);
		}
		ca = ca->next;
	}
}