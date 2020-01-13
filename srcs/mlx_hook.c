/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:53:33 by braimbau          #+#    #+#             */
/*   Updated: 2020/01/13 21:38:07 by selgrabl         ###   ########.fr       */
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
	t_rtx	*rtx = param;
	int i;
	t_cam	*cam;

	i = 0;
	cam = rtx->cam;
	if (key == 123 && rtx->cam_num > 0)
		rtx->cam_num--;
	while(i < rtx->cam_num)
	{
		cam = cam->next;
		if (cam->filter == 'l')
			cam = cam->next;
		i++;
	}
	if (key == 124 && cam->next && (cam->next->filter != 'r' || cam->next->next))
	{
		rtx->cam_num++;
		cam = cam->next;
			if (cam->filter == 'l')
		cam = cam->next;
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