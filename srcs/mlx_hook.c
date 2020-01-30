/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:53:33 by braimbau          #+#    #+#             */
/*   Updated: 2020/01/27 13:31:12 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

int		exit_hook(void *param)
{
	(void)param;
	exit(0);
	return(EXIT_SUCCESS);
}

int		key_hook(int key, void *param)
{
	printf("%d\n", key);
	t_rtx	*rtx = param;
	int i;
	t_cam	*cam;

	i = 0;
	cam = rtx->cam;
	if (key == PREV_CAM && rtx->cam_num > 0)
		rtx->cam_num--;
	while(i < rtx->cam_num)
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
		anti_aliesing(cam, rtx);
		filter(cam->filter, rtx->res, &(cam->id));
	}
	mlx_put_image_to_window(rtx->mlx_ptr, rtx->mlx_win, cam->img, 0, 0);
	if (key == 53)
		exit(0);
	return(EXIT_SUCCESS);
}

void	mlx_put_pixel_img(int x, int y, char **id, int sl, t_color color)
{
	(*id)[(x + (y * sl)) * 4] = (char)color.b;
	(*id)[((x + (y * sl)) * 4) + 1] = (char)color.g;
	(*id)[((x + (y * sl)) * 4 )+ 2] = (char)color.r;
}