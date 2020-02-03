/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirtx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 10:39:59 by braimbau          #+#    #+#             */
/*   Updated: 2020/02/03 10:54:18 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

void		init_main(t_rtx *rtx, int argc, char **argv, void *mlx_ptr)
{
	*rtx = parseke(argc, argv, mlx_ptr);
	rtx->mlx_ptr = mlx_ptr;
	rtx->cam_num = 0;
	rtx->aa = (rtx->aa != 2) ? 1 : rtx->aa;
}

int			main(int argc, char **argv)
{
	void	*mlx_ptr;
	t_rtx	rtx;
	t_cam	*ca;
	int		i;

	i = 0;
	mlx_ptr = mlx_init();
	init_main(&rtx, argv, argv, mlx_ptr);
	ca = rtx.cam;
	while (ca)
	{
		cal_cam(&rtx, rtx.mlx_ptr, ca);
		filter(ca->filter, rtx.res, &(ca->id));
		anti_aliasing(ca, &rtx);
		ca = ca->next;
	}
	make_3d(&(rtx.cam), rtx.res);
	rtx.mlx_win = mlx_new_window(rtx.mlx_ptr, rtx.res.x, rtx.res.y, "miniRTX");
	mlx_hook(rtx.mlx_win, DestroyNotify, StructureNotifyMask, exit_hook, NULL);
	mlx_key_hook(rtx.mlx_win, key_hook, &rtx);
	mlx_put_image_to_window(rtx.mlx_ptr, rtx.mlx_win, rtx.cam->img, 0, 0);
	if (rtx.save)
		export_to_bmp(rtx.cam->id, rtx.res);
	mlx_loop(rtx.mlx_ptr);
	return (EXIT_SUCCESS);
}

void		multi_thread(t_cam *cam, t_rtx *rtx)
{
	t_thread		tt[CORE];
	pthread_mutex_t mutex;
	pthread_mutex_t mutex2;
	pthread_t		thread[CORE];
	int				i;

	i = 0;
	pthread_mutex_init(&mutex, NULL);
	while (i < CORE)
	{
		rtx->coor.x = rtx->res.x / CORE * i;
		tt[i].i = i;
		tt[i].mutex[0] = &mutex;
		tt[i].mutex[1] = &mutex2;
		tt[i].rtx = *rtx;
		tt[i].cam = *cam;
		pthread_create(&thread[i], NULL, &show, &tt[i]);
		i++;
	}
	while (i)
	{
		pthread_join(thread[i - 1], NULL);
		i--;
	}
}

void		*show(void *arg)
{
	t_thread	*tt;
	float		pw;
	float		ph;
	t_vec		pix;

	tt = (t_thread*)arg;
	pw = 2 * tan((float)tt->cam.fov / 360 * M_PI) / tt->rtx.res.x * tt->rtx.ar;
	ph = 2 * tan((float)tt->cam.fov / 360 * M_PI) / tt->rtx.res.y;
	while (tt->rtx.coor.x < ceil((float)tt->rtx.res.x / (float)CORE *
	(float)(tt->i + 1)))
	{
		tt->rtx.coor.y = 0;
		while (tt->rtx.coor.y < tt->rtx.res.y)
		{
			pix = cal_pix(tt, pw, ph);
			tt->cam.ray = normalize(min(tt->cam.origin, pix));
			tt->cam.ray = rotate_vec(tt->cam.ray, tt->cam.right, tt->cam.rot.x);
			tt->cam.ray = rotate_vec(tt->cam.ray, tt->cam.up, tt->cam.rot.y);
			tt->cam.ray = rotate_vec(tt->cam.ray, tt->cam.vec, tt->cam.rot.z);
			mlx_put_pixel_img(init_res(tt->rtx.coor.x, tt->rtx.coor.y), &(tt->cam.id),
			tt->rtx.res.x, cal_col((tt->cam), (tt->rtx), 0));
			tt->rtx.coor.y++;
		}
		tt->rtx.coor.x++;
	}
	return (NULL);
}
