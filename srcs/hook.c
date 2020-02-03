/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raimbaultbrieuc <raimbaultbrieuc@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:53:33 by braimbau          #+#    #+#             */
/*   Updated: 2020/02/03 15:08:28 by raimbaultbr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

int				exit_hook(void *param)
{
	t_rtx *rtx;
	
	rtx = (t_rtx*)param;
	free_lists(rtx->cam, rtx->light, rtx->shape);
	exit(0);
	return (EXIT_SUCCESS);
}

static t_cam	*multi_cam(t_rtx *rtx, int key)
{
	int		i;
	t_cam	*cam;

	i = 0;
	cam = rtx->cam;
	if (key == PREV_CAM && rtx->cam_num > 0)
		rtx->cam_num--;
	while (i < rtx->cam_num)
	{
		cam = cam->next;
		i++;
	}
	if (key == NEXT_CAM && cam->next)
	{
		rtx->cam_num++;
		cam = cam->next;
	}
	return (cam);
}

int				key_hook(int key, void *param)
{
	t_rtx	*rtx;
	t_cam	*cam;

	rtx = param;
	cam = multi_cam(rtx, key);
	make_rotation(key, cam);
	make_translation(key, cam);
	apply_filter(key, cam);
	if (key == QUA_UP)
		if (rtx->aa < 2)
			rtx->aa *= 2;
	if (key == QUA_DO)
		if (rtx->aa > 0.125)
			rtx->aa /= 2;
	if (key != PREV_CAM && key != NEXT_CAM && cam->filter != 'r')
	{
		cal_cam(rtx, rtx->mlx_ptr, cam);
		anti_aliasing(cam, rtx);
		filter(cam->filter, rtx->res, &(cam->id));
	}
	mlx_put_image_to_window(rtx->mlx_ptr, rtx->mlx_win, cam->img, 0, 0);
	if (key == 53)
	{
		exit(0);
		free_lists(rtx->cam, rtx->light, rtx->shape);
	}
	return (EXIT_SUCCESS);
}
