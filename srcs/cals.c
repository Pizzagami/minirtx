/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cals.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raimbaultbrieuc <raimbaultbrieuc@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 10:15:53 by braimbau          #+#    #+#             */
/*   Updated: 2020/02/03 14:58:24 by raimbaultbr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

t_vec			cal_pix(t_thread *tt, float pw, float ph)
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

static t_color	make_color(t_rtx *rtx, t_tg *shape, float dist, t_cam *cam)
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

t_color			cal_col(t_cam cam, t_rtx rtx, int bound)
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

t_color			cal_lit(t_cam cam, t_tg shape, t_rtx *rtx, float dist)
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
		if ((shape.type == 4 || shape.type == 0 || shape.type == 3)
		&& dot(shape.normal, cam.ray) > 0)
			shape.normal = fois(shape.normal, -1);
		c = dot(light, shape.normal);
		c = (c < 0) ? 0 : c;
		c *= cal_lite_inter(*rtx, li, point, shape);
		color = color_add(color, cosha(c, li->color, shape.color), 1);
		li = li->next;
	}
	return (color);
}

void			*cal_cam(t_rtx *rtx, void *mlx_ptr, t_cam *cam)
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
