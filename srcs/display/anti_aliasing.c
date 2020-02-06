/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 10:38:58 by selgrabl          #+#    #+#             */
/*   Updated: 2020/02/06 15:56:45 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

static void	make_aa(t_rtx *rtx, t_cam *cam, char **id)
{
	t_color	color;
	int		x;
	int		y;

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
			put_pixel(init_res(x, y), id, rtx->res.x, color);
			y++;
		}
		x++;
	}
}

static void	make_lq(t_rtx *rtx, t_cam *cam, char **id)
{
	t_color color;
	int		x;
	int		y;

	x = 0;
	while (x < rtx->res.x)
	{
		y = 0;
		while (y < rtx->res.y)
		{
			rtx->res.x /= 1 / rtx->aa;
			color = cp(x / (1 / rtx->aa), y / (1 / rtx->aa), cam->id, rtx->res);
			rtx->res.x *= 1 / rtx->aa;
			put_pixel(init_res(x, y), id, rtx->res.x, color);
			y++;
		}
		x++;
	}
}

void		anti_aliasing(t_cam *cam, t_rtx *rtx)
{
	int		x;
	void	*img_ptr;
	char	*id;

	if (rtx->aa == 1)
		return ;
	rtx->res.x /= rtx->aa;
	rtx->res.y /= rtx->aa;
	img_ptr = mlx_new_image(rtx->mlx_ptr, rtx->res.x, rtx->res.y);
	id = mlx_get_data_addr(img_ptr, &x, &x, &x);
	if (rtx->aa > 1)
		make_aa(rtx, cam, &id);
	else
		make_lq(rtx, cam, &id);
	cam->id = id;
	cam->img = img_ptr;
}
