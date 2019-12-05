/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirtx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 19:03:43 by braimbau          #+#    #+#             */
/*   Updated: 2019/12/05 14:16:44 by selgrabl         ###   ########.fr       */
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
	t_light *la;
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
		la = &l1;
		lfois(la->color, la->ratio);
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
	void	*mlx_ptr;
	void	*mlx_win;
	float	aspect_ratio;
	t_rtx	rtx;

	rtx = parseke(argc, argv);
	mlx_ptr = mlx_init();
	mlx_win = mlx_new_window(mlx_ptr, rtx.res.x, rtx.res.y, "Pizza");
	rtx.coor.x = 0;
	while(rtx.coor.x < rtx.res.x)
	{
		rtx.coor.y = 0;
		while (rtx.coor.y < rtx.res.y)
		{
			aspect_ratio = (float)rtx.res.x / (float)rtx.res.y; // assuming width > height 
			rtx.cam->ray.x = (2 * ((rtx.coor.x + 0.5) / rtx.res.x) - 1) *
			tan((float)rtx.cam->fov /2 /180 * M_PI) * aspect_ratio;
			rtx.cam->ray.y = (1 - (2 * ((rtx.coor.y + 0.5) / rtx.res.y))) *
			tan((float)rtx.cam->fov /2 /180 * M_PI);
			rtx.cam->ray.z = -1;
			rtx.cam->ray = normalize(rtx.cam->ray);
			mlx_pixel_put(mlx_ptr, mlx_win, rtx.coor.x, rtx.coor.y,
			rgbtoon(cal_col(*(rtx.cam), *(rtx.shape), *(rtx.light))));
			rtx.coor.y++;
		}
		rtx.coor.x++;
	}
	void *r;
	mlx_hook(mlx_win, DestroyNotify, StructureNotifyMask, exit_hook, r);
	mlx_key_hook(mlx_win, key_hook, r);
	mlx_loop(mlx_ptr);
}
