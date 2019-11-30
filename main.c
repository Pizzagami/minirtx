/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 19:03:43 by braimbau          #+#    #+#             */
/*   Updated: 2019/11/30 15:49:41 by selgrabl         ###   ########.fr       */
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

t_color		cal_col(t_cam cam, t_tg shape, t_light l1)
{	
	t_color color;
	t_vec normal;
	t_vec light;
	t_vec point;
	float dist;
	float c;
	float amb = 0;

	color.r = 0;
	color.g = 0;
	color.b = 0;
	dist = 1;
	dist = find_dist(cam, shape);
	if (dist != -1.0)
	{
		color.r = amb * shape.color.r;
		color.g = amb * shape.color.g;
		color.b = amb * shape.color.b;
		t_light *la;
		la = &l1;
		while (la != NULL)
		{
			point = plus(cam.origin, fois(cam.ray, dist));
			light = normalize(min(la->pos, point));
			if (shape.type == 0 || shape.type == 4)
			normal = shape.vec;
			else
			normal = normalize(min(point, shape.center));
			c = dot(light, normal);
			if (c < 0)
				c = -c;
			color.r += c * la->color.r;
			color.g += c * la->color.g;
			color.b += c * la->color.b;
			la = la->next;
		}
	if (color.r > shape.color.r)
		color.r = shape.color.r;
	if (color.g > shape.color.g)
		color.g = shape.color.g;
	if (color.b > shape.color.b)
		color.b = shape.color.b;
	}
		return (color);
}
int main(int argc, char **argv)
{
	t_coor coor;
	void    *mlx_ptr;
	void    *mlx_win;
	t_cam	cam;
	t_vec   center;
	float   iAR;
	int fov;
	t_tg shape;
	t_rtx		rtx;
	rtx = parseke(argv[1]);
	return(0);
	shape.dia	= 9;
	shape.vec.x = 0.01;
	shape.vec.y = 0.01;
	shape.vec.z = 0.99;
	shape.type	= 4;
	shape.hi	= 5;
	fov = ft_atoi(argv[3]);
	coor.res_x = ft_atoi(argv[1]);
	coor.res_y = ft_atoi(argv[2]);
	cam.ray.z = 623.5;
	shape.center.x = 0;
	shape.center.y = 0;
	shape.center.z = -10;
	shape.color.r = 255;
	shape.color.b = 255;
	shape.color.g = 255;
	cam.origin.x = 0;
	cam.origin.y = 0;
	cam.origin.z = 0;

	t_light l1;
	l1.pos.x = 0;
	l1.pos.y = 0;
	l1.pos.z = 0;
	l1.color.r = 255;
	l1.color.g = 0;
	l1.color.b = 0;
	t_light l2;
	l2.pos.x = -7;
	l2.pos.y = 8;
	l2.pos.z = 0;
	l2.color.r = 0;
	l2.color.g = 0;
	l2.color.b = 255;
	l2.next = NULL;
	l1.next = NULL;

	t_color back;
	back.r = 0;
	back.g = 0;
	back.b = 0;

	mlx_ptr = mlx_init();
	
	mlx_win = mlx_new_window(mlx_ptr, coor.res_x, coor.res_y, "Pizza");
	coor.x = 0;
	while(coor.x < coor.res_x)
	{
		coor.y = 0;
		while (coor.y < coor.res_y)
		{
			iAR = (float)coor.res_x / (float)coor.res_y; // assuming width > height 
			cam.ray.x = (2 * ((coor.x + 0.5f) / (float)coor.res_x) - 1) * tan((float)fov /2 /180 * M_PI) * iAR;
			cam.ray.y = (1 - (2 * ((coor.y + 0.5f) / (float)coor.res_y))) * tan((float)fov /2 /180 * M_PI);
			cam.ray.z = -1;
			cam.ray = normalize(cam.ray);
			mlx_pixel_put(mlx_ptr, mlx_win, coor.x, coor.y, rgbtoon(cal_col(cam, shape, l1)));
			coor.y++;
		}
		coor.x++;
	}
	void *r;
	mlx_hook(mlx_win, DestroyNotify, StructureNotifyMask, exit_hook, r);
	mlx_key_hook(mlx_win, &key_hook, r);
	mlx_loop(mlx_ptr);
}
