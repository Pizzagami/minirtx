/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirtx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 19:03:43 by braimbau          #+#    #+#             */
/*   Updated: 2020/01/19 16:42:46 by braimbau         ###   ########.fr       */
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

t_color		cal_col(t_cam cam, t_rtx rtx, int bound)
{	
	t_color color;
	float dist;
	float ldist;
	t_tg shape;
	t_tg *sh;
	
	if (bound > 10)
		return(color_init(0,0,0));
	sh = rtx.shape;
	dist = -1;
	while (sh)
	{
		ldist = find_dist(cam.origin, cam.ray, sh);
		if (ldist != - 1 && (dist == - 1 || ldist < dist))
		{
			dist = ldist;
			shape = *sh;
		}
		sh = sh->next;
	}
	if (shape.type == 1)
			shape.normal = normalize(min(plus(cam.origin, fois(cam.ray, dist)), shape.center));
	if (dist != -1.0)
	{
		color = color_add(cosha(rtx.amb.ratio, rtx.amb.color, shape.color),
		cal_lit(cam, shape, &rtx, dist), 1);
		color = color_cap(color, shape.color);
	}
	if (shape.refl && dist != -1.0)
	{
		cam.ray = min(cam.ray, fois(shape.normal , 2 * dot(cam.ray, shape.normal)));
		color = color_mix(color, cal_col(cam, rtx, bound + 1), 1 - shape.refl, shape.refl);
	}
	if (shape.trans && dist != -1.0)
	{
		if (shape.type == 1)
			cam.origin = plus(cam.origin, fois(cam.ray, dist + shape.dia));
		else
			cam.origin = plus(cam.origin, fois(cam.ray, dist + 0.00001)); 
		color = color_mix(color, cal_col(cam, rtx, bound + 1), 1 - shape.trans, shape.trans);
	}
	if (dist == -1)
		return(color_init(0,0,0));
	return (color);
}

t_color         cal_lit(t_cam cam, t_tg shape, t_rtx *rtx, float dist)
{
	t_vec	light;
	t_vec	point;
	t_color	color;
	float c;
	t_light *li;

	color = color_init(0,0,0);
	li = rtx->light;
	while (li)
	{
		point = plus(cam.origin, fois(cam.ray, dist));
		light = normalize(min(li->pos, point));
		if(dot(shape.normal, cam.ray) > 0)
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

int main(int argc, char **argv)
{
	void	*mlx_win_load;
	t_rtx	rtx;
	t_cam	*ca;
	int		i;

	i = 0;
	rtx = parseke(argc, argv);
	rtx.cam_num = 0;
	rtx.mlx_ptr = mlx_init();
	mlx_win_load = mlx_new_window(rtx.mlx_ptr, 550, 50, "Loading ...");
	ca = rtx.cam;
	while (ca)
	{
		cal_cam(&rtx, rtx.mlx_ptr, mlx_win_load, ca);
		filter(ca->filter, rtx.res, &(ca->id));
		ca = ca->next;
	}
	make_3d(&rtx.cam, rtx.res);
	mlx_destroy_window(rtx.mlx_ptr, mlx_win_load);
	rtx.mlx_win = mlx_new_window(rtx.mlx_ptr, rtx.res.x, rtx.res.y, "miniRTX");
	mlx_hook(rtx.mlx_win, DestroyNotify, StructureNotifyMask, exit_hook, NULL);
	mlx_key_hook(rtx.mlx_win, key_hook, &rtx);
	mlx_put_image_to_window(rtx.mlx_ptr, rtx.mlx_win, rtx.cam->img, 0, 0);
	if (rtx.save)
		export_to_bmp(rtx.cam->id, rtx.res);
	mlx_loop(rtx.mlx_ptr);
	return(EXIT_SUCCESS);
}

void	*cal_cam(t_rtx *rtx, void *mlx_ptr, void *mlx_win_load, t_cam *cam)
{
	float	aspect_ratio;
	int		x;

	cam->img = mlx_new_image(mlx_ptr, rtx->res.x, rtx->res.y);
	cam->id = mlx_get_data_addr(cam->img, &x, &x, &x);
	mlx_clear_window(mlx_ptr, mlx_win_load);
	aspect_ratio = (float)rtx->res.x / (float)rtx->res.y;
	rtx->coor.x = 0;
	while(rtx->coor.x < rtx->res.x)
	{
		rtx->coor.y = 0;
		while (rtx->coor.y < rtx->res.y)
		{
			cam->ray.x = (2 * ((rtx->coor.x + 0.5) / rtx->res.x) - 1) *
			tan((float)cam->fov / 2.0 / 180.0 * M_PI) * aspect_ratio;
			cam->ray.y = (1 - (2 * ((rtx->coor.y + 0.5) / rtx->res.y))) *
			tan((float)cam->fov /2 /180 * M_PI);
			cam->ray.z = -1;
			cam->ray = normalize(cam->ray);
			t_matrix rotation_x = init_matrix(init_vec(1,0,0), init_vec(0, cos(cam->rot.x), -sin(cam->rot.x)), init_vec(0, sin(cam->rot.x), cos(cam->rot.x)));
			t_matrix rotation_y = init_matrix(init_vec(cos(cam->rot.y),0,sin(cam->rot.y)), init_vec(0, 1, 0), init_vec(-sin(cam->rot.y), 0, cos(cam->rot.y)));
			t_matrix rotation_z = init_matrix(init_vec(cos(cam->rot.z),-sin(cam->rot.z), 0), init_vec(sin(cam->rot.z), cos(cam->rot.z), 0), init_vec(0, 0, 1));
			cam->ray = vec_matrixed(cam->ray, rotation_x);
			cam->ray = vec_matrixed(cam->ray, rotation_y);
			cam->ray = vec_matrixed(cam->ray, rotation_z);
			mlx_put_pixel_img(rtx->coor.x, rtx->coor.y, &(cam->id), rtx->res.x, cal_col(*(cam), *rtx, 0));
			rtx->coor.y++;
		}
		//if ((int)(rtx->coor.x / rtx->res.x * 100) != (int)((rtx->coor.x - 1)/rtx->res.x * 100) || rtx->coor.x == 0)
			//refresh_loading_bar(rtx, mlx_win_load, rtx->coor.x / rtx->res.x * 100);
		rtx->coor.x++;
	}
	return(cam->img);
}