/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:53:33 by braimbau          #+#    #+#             */
/*   Updated: 2020/01/19 16:42:47 by braimbau         ###   ########.fr       */
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
		if (cam->filter == 'l')
			cam = cam->next;
		i++;
	}
	if (key == NEXT_CAM && cam->next && (cam->next->filter != 'r' || cam->next->next))
	{
		rtx->cam_num++;
		cam = cam->next;
			if (cam->filter == 'l')
		cam = cam->next;
	}
	if (key == RXU)
		cam->rot.x += 0.05;
	if (key == RXD)
		cam->rot.x -= 0.05;
	if (key == RYU)
		cam->rot.y += 0.05;
	if (key == RYD)
		cam->rot.y -= 0.05;
	if (key == RZU)
		cam->rot.z += 0.05;
	if (key == RZD)
		cam->rot.z -= 0.05;
	if (key == TXU)
		cam->origin.x += 5;
	if (key == TXD)
		cam->origin.x -= 5;
	if (key == TYU)
		cam->origin.y += 5;
	if (key == TYD)
		cam->origin.y -= 5;
	if (key == TZU)
		cam->origin.z += 5;
	if (key == TZD)
		cam->origin.z -= 5;
	if (key == FI_R)
		cam->filter = 'R';
	if (key == FI_G)
		cam->filter = 'G';
	if (key == FI_B)
		cam->filter = 'B';
	if (key == FI_P)
		cam->filter = 'P';
	if (key == FI_C)
		cam->filter = 'C';
	if (key == FI_Y)
		cam->filter = 'Y';
	if (key == FI_W)
		cam->filter = 'W';
	if (key == FI_N)
		cam->filter = 'N';
	if (key == FI_S)
		cam->filter = 'S';
	if (key == FI_RST)
		cam->filter = 0;
	cal_cam(rtx, rtx->mlx_ptr, rtx->mlx_win, cam);
	filter(cam->filter, rtx->res, &(cam->id));
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