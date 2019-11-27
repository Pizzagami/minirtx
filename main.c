/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 19:03:43 by braimbau          #+#    #+#             */
/*   Updated: 2019/11/27 16:33:32 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

float find_dist(t_vec ray, t_vec origin, t_vec center, int r)
{
	float x1;


	float x2;
	int s;
	int mlp;

	s = second_degre(dot(ray, ray), 2 * dot(ray, min(origin, center)), dot(min(origin, center), min(origin, center)) - pow(r, 2), &x1, &x2);
	if (s == 1 && x1 > 0)
		return (x1);
	else if (s == 2 && (x1 > 0 && x2 > 0))
	{
		if (x2 > 0)
			return ((x1 <= x2 && x1 > 0) ? x1 : x2);
		return (x1);
	}
	return (-1);
}

int rgbtoon(int r, int g, int b)
{
	int ret;
	return(r * 65536 + g * 256 + b);
}
int main(int argc, char **argv)
{
	int     res_x;
	int     res_y;
	void    *mlx_ptr;
	void    *mlx_win;
	float     x;
	float     y;
	float   dist;
	t_vec   ray;
	t_vec   origin;
	t_vec   center;
	int r = 5;
	float   iAR;
	float   Px;
	float   Py;
	int fov;
	float c;
	int color;
	t_vec normal;
	t_vec light;
	t_vec point;

	fov = ft_atoi(argv[3]);
	res_x = ft_atoi(argv[1]);
	res_y = ft_atoi(argv[2]);
	ray.z = 623.5;
	center.x = 5;
	center.y = 7;
	center.z = -20;
	origin.x = 0;
	origin.y = 0;
	origin.z = 0;

	t_vec lightPos;

	lightPos.x = 0;
	lightPos.y = 0;
	lightPos.z = 0;
	mlx_ptr = mlx_init();
	mlx_win = mlx_new_window(mlx_ptr, res_x, res_y, "Mael best");
	x = 0;
	while(x < res_x)
		{
			y = 0;
			while (y < res_y)
			{
				iAR = (float)res_x / (float)res_y; // assuming width > height 
				Px = (2 * ((x + 0.5f) / (float)res_x) - 1) * tan((float)fov /2 /180 * M_PI) * iAR;
				Py = (1 - (2 * ((y + 0.5f) / (float)res_y))) * tan((float)fov /2 /180 * M_PI);
				ray.y = Py;
				ray.x = Px;
				ray.z = -1;
				dist = find_dist(normalize(ray), origin, center, r);
				if (dist == -1)
					color = rgbtoon(0,0,0);
				else
				{
					point = plus(origin, fois(ray, dist));
					light = normalize(min(lightPos, point));
					normal = normalize(min(point, center));
					c = dot(light, normal);
					color = rgbtoon(c * 255, c * 255, c * 255);
				}
				mlx_pixel_put(mlx_ptr, mlx_win, x, y, color);
				y++;
			}
			x++;
		}
	mlx_loop(mlx_ptr);
}
