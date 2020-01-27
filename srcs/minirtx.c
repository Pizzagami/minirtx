/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirtx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 10:39:59 by braimbau          #+#    #+#             */
/*   Updated: 2020/01/27 13:23:55 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

t_color		make_color(t_rtx *rtx, t_tg *shape, float dist, t_cam *cam)
{
	t_color color;

	color = color_add(cosha(rtx->amb.ratio, rtx->amb.color, shape->color),
	cal_lit(*cam, *shape, rtx, dist), 1);
	color = color_cap(color, shape->color);
	if (shape->refl)
	{
		cam->ray = min(cam->ray, fois(shape->normal, 2 * dot(cam->ray,
		shape->normal)));
		color = color_mix(color, cal_col(*cam, *rtx, rtx->bound + 1),
		1 - shape->refl, shape->refl);
	}
	if (shape->trans)
	{
		if (shape->type == 1)
			cam->origin = plus(cam->origin, fois(cam->ray, dist + shape->dia));
		else
			cam->origin = plus(cam->origin, fois(cam->ray, dist + 0.00001));
		color = color_mix(color, cal_col(*cam, *rtx, rtx->bound + 1),
		1 - shape->trans, shape->trans);
	}
	if (shape->dam)
		damier(plus(cam->origin, fois(cam->ray, dist)), shape, &color, dist);
	return (color);
}

t_color		cal_col(t_cam cam, t_rtx rtx, int bound)
{
	float	dist;
	float	ldist;
	t_tg	shape;
	t_tg	*sh;

	if (bound > 10)
		return (color_init(0, 0, 0));
	sh = rtx.shape;
	dist = -1;
	while (sh)
	{
		ldist = find_dist(cam.origin, cam.ray, sh);
		if (ldist != -1 && (dist == -1 || ldist < dist))
		{
			dist = ldist;
			shape = *sh;
		}
		sh = sh->next;
	}
	shape.normal = find_normal(shape, cam, dist);
	make_mapping(&shape);
	rtx.bound = bound;
	return ((dist != -1) ? make_color(&rtx, &shape, dist, &cam)
	: color_init(0, 0, 0));
}

t_color		cal_lit(t_cam cam, t_tg shape, t_rtx *rtx, float dist)
{
	t_vec	light;
	t_vec	point;
	t_color	color;
	float	c;
	t_light	*li;

	color = color_init(0, 0, 0);
	li = rtx->light;
	while (li)
	{
		point = plus(cam.origin, fois(cam.ray, dist));
		if (li->para.x || li->para.y || li->para.z)
			light = fois(li->para, -1);
		else
			light = normalize(min(li->pos, point));
		if (dot(shape.normal, cam.ray) > 0)
			shape.normal = fois(shape.normal, -1);
		c = dot(light, shape.normal);
		if (c < 0)
			c = 0;
		c *= cal_lite_inter(*rtx, li, point, shape);
		color = color_add(color, cosha(c, li->color, shape.color), 1);
		li = li->next;
	}
	return (color);
}

int			main(int argc, char **argv)
{
	void	*mlx_ptr;
	t_rtx	rtx;
	t_cam	*ca;
	int		i;

	i = 0;
	mlx_ptr = mlx_init();
	rtx = parseke(argc, argv, mlx_ptr);
	rtx.mlx_ptr = mlx_ptr;
	rtx.cam_num = 0;
	if (rtx.aa != 2)
		rtx.aa = 1;
	ca = rtx.cam;
	while (ca)
	{
		cal_cam(&rtx, rtx.mlx_ptr, ca);
		filter(ca->filter, rtx.res, &(ca->id));
		anti_aliesing(ca, &rtx);
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

void		*cal_cam(t_rtx *rtx, void *mlx_ptr, t_cam *cam)
{
	int		x;

	rtx->res.x *= rtx->aa;
	rtx->res.y *= rtx->aa;
	rtx->ar = (float)rtx->res.x / (float)rtx->res.y;
	cam->img = mlx_new_image(mlx_ptr, rtx->res.x, rtx->res.y);
	cam->id = mlx_get_data_addr(cam->img, &x, &x, &x);
	multi_thread(cam, rtx);
	return (cam->img);
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

t_vec		rotate_vec(t_vec base, t_vec rot, float angle)
{
	float		c;
	float		s;
	t_matrix	matrix;

	c = cos(angle);
	s = sin(angle);
	matrix.a = init_vec(rot.x * rot.x * (1 - c) + c, rot.x * rot.y * (1 - c)
	- rot.z * s, rot.x * rot.z * (1 - c) + rot.y * s);
	matrix.b = init_vec(rot.x * rot.y * (1 - c) + rot.z * s, rot.y * rot.y *
	(1 - c) + c, rot.y * rot.z * (1 - c) - rot.x * s);
	matrix.c = init_vec(rot.x * rot.z * (1 - c) - rot.y * s, rot.y * rot.z *
	(1 - c) + rot.x * s, rot.z * rot.z * (1 - c) + c);
	base = vec_matrixed(base, matrix);
	return (base);
}

t_vec		cal_pix(t_thread *tt, float pw, float ph)
{
	t_vec pix;

	pix = plus(tt->cam.origin, min(tt->cam.vec, fois(tt->cam.right,
	pw * (tt->rtx.res.x / 2))));
	pix = plus(pix, fois(tt->cam.up, (tt->rtx.res.y / 2) * ph));
	pix = plus(pix, fois(tt->cam.right, pw / 2));
	pix = min(pix, fois(tt->cam.up, ph / 2));
	pix = plus(pix, fois(tt->cam.right, pw * tt->rtx.coor.x));
	pix = min(pix, fois(tt->cam.up, ph * tt->rtx.coor.y));
	return (pix);
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
	while (tt->rtx.coor.x < tt->rtx.res.x / CORE * (tt->i + 1))
	{
		tt->rtx.coor.y = 0;
		while (tt->rtx.coor.y < tt->rtx.res.y)
		{
			pix = cal_pix(tt, pw, ph);
			tt->cam.ray = normalize(min(tt->cam.origin, pix));
			tt->cam.ray = rotate_vec(tt->cam.ray, tt->cam.right, tt->cam.rot.x);
			tt->cam.ray = rotate_vec(tt->cam.ray, tt->cam.up, tt->cam.rot.y);
			tt->cam.ray = rotate_vec(tt->cam.ray, tt->cam.vec, tt->cam.rot.z);
			mlx_put_pixel_img(tt->rtx.coor.x, tt->rtx.coor.y, &(tt->cam.id),
			tt->rtx.res.x, cal_col((tt->cam), (tt->rtx), 0));
			tt->rtx.coor.y++;
		}
		tt->rtx.coor.x++;
	}
	return (NULL);
}
