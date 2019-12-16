/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirtx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 19:03:43 by braimbau          #+#    #+#             */
/*   Updated: 2019/12/16 17:34:38 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

int rgbtoon(t_color color)
{
	if (color.r > 255)
	color.r = 255;
	if (color.g > 255)
	color.g = 255;
	if (color.b > 255)
	color.b = 255;
	if (color.r < 0)
	color.r = 0;
	if (color.g < 0)
	color.g = 0;
	if (color.b < 0)
	color.b = 0;
	return(color.r * 65536 + color.g * 256 + color.b);
}

t_color		cal_col(t_cam cam, t_rtx rtx)
{	
	t_color color;
	float dist;
	float ldist;
	//float c;
	t_tg shape;
	t_tg *sh;
	
	sh = rtx.shape;
	color.r = 0;
	color.g = 0;
	color.b = 0;
	dist = -1;
	while (sh)
	{
		sh->vec = (sh->type == 3) ? normalize(cross(min(sh->p2, sh->p1),
   		min(sh->p3, sh->p1))) : sh->vec;
		ldist = find_dist(cam.origin, cam.ray, *sh);
		if (ldist != -1)
		if (ldist != - 1 && (dist == - 1 || ldist < dist))
		{
			dist = ldist;
			shape = *sh;
		}
		sh = sh->next;
	}
	if (dist != -1.0)
	{
		color.r = rtx.amb.ratio * rtx.amb.color.r / 255 * shape.color.r;
		color.g = rtx.amb.ratio * rtx.amb.color.g / 255 * shape.color.g;
		color.b = rtx.amb.ratio * rtx.amb.color.b / 255 * shape.color.b;
		color = color_add(color, cal_lit(cam, shape, rtx, dist), 1);
	if (color.r > shape.color.r)
		color.r = shape.color.r;
	if (color.g > shape.color.g)
		color.g = shape.color.g;
	if (color.b > shape.color.b)
		color.b = shape.color.b;
	}
	return (color);
}

t_color         cal_lit(t_cam cam, t_tg shape, t_rtx rtx, float dist)
{
	t_vec normal;
	t_vec light;
	t_vec point;
	t_color color;
	float c;
	t_tg *sh;
	t_light *li;
	float ldist;
	color.r = 0;
	color.g = 0;
	color.b = 0;
	li = rtx.light;
	while (li)
	{
		sh = rtx.shape;
		point = plus(cam.origin, fois(cam.ray, dist));
		light = normalize(min(li->pos, point));
		if (shape.type == 0 || shape.type == 3 || shape.type == 4 || shape.type == 5)
			normal = shape.vec;
		else
			normal = normalize(min(point, shape.center));
		c = dot(light, normal);
		if (c < 0)
		{
			if (shape.type == 0 || shape.type == 3 || shape.type == 4 || shape.type == 5)
				c = -c;
			else
				c = 0;
		}
		ldist = find_dist(li->pos, min(point, li->pos), shape);
		while (sh)
		{
			if (find_dist(li->pos, min(point, li->pos), *sh) < ldist &&
				find_dist(li->pos, min(point, li->pos), *sh) > 0)
				c = 0;
			sh = sh->next;
		}
		color.r += c * li->color.r * shape.color.r /255;
		color.g += c * li->color.g * shape.color.g /255;
		color.b += c * li->color.b * shape.color.b /255;
		li = li->next;
	}
	return (color);
}


int main(int argc, char **argv)
{
	void	*mlx_ptr;
	void	*mlx_win;
	void	*img;
	char	*id;
	void	*r;
	int		bpp;
	int		sl;
	int		endian;
	float	aspect_ratio;
	t_rtx	rtx;

	r = NULL;
	rtx = parseke(argc, argv);
	mlx_ptr = mlx_init();
	mlx_win = mlx_new_window(mlx_ptr, rtx.res.x, rtx.res.y, "miniRTX");
	img = mlx_new_image(mlx_ptr, rtx.res.x, rtx.res.y);
	id = mlx_get_data_addr(img, &bpp, &sl, &endian);
	rtx.coor.x = 0;
	while(rtx.coor.x < rtx.res.x)
	{
		rtx.coor.y = 0;
		while (rtx.coor.y < rtx.res.y)
		{
			aspect_ratio = (float)rtx.res.x / (float)rtx.res.y; // assuming width > height 
			rtx.cam->ray.x = (2 * ((rtx.coor.x + 0.5) / rtx.res.x) - 1) *
			tan((float)rtx.cam->fov / 2.0 / 180.0 * M_PI) * aspect_ratio;
			rtx.cam->ray.y = (1 - (2 * ((rtx.coor.y + 0.5) / rtx.res.y))) *
			tan((float)rtx.cam->fov /2 /180 * M_PI);
			rtx.cam->ray.z = -1;
			rtx.cam->ray = normalize(rtx.cam->ray);
			mlx_put_pixel_img(rtx.coor.x, rtx.coor.y, &id, rtx.res.x, cal_col(*(rtx.cam), rtx));
			rtx.coor.y++;
		}
		rtx.coor.x++;
	}
	mlx_hook(mlx_win, DestroyNotify, StructureNotifyMask, exit_hook, r);
	mlx_key_hook(mlx_win, key_hook, r);
	mlx_put_image_to_window(mlx_ptr, mlx_win, img, 0, 0);
	mlx_loop(mlx_ptr);
	return(EXIT_SUCCESS);
}