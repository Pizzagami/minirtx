/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:53:33 by braimbau          #+#    #+#             */
/*   Updated: 2020/02/01 11:41:49 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

int		exit_hook(void *param)
{
	(void)param;
	exit(0);
	return (EXIT_SUCCESS);
}

int		key_hook(int key, void *param)
{
	t_rtx	*rtx;
	int		i;
	t_cam	*cam;

	rtx = param;
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
		exit(0);
	return (EXIT_SUCCESS);
}