/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 19:03:43 by braimbau          #+#    #+#             */
/*   Updated: 2019/11/28 17:11:27 by braimbau         ###   ########.fr       */
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
	if (r > 255)
	r = 255;
	if (g > 255)
	g = 255;
	if (b > 255)
	b = 255;
	if (r < 0)
	r = 0;
	if (g < 0)
	g = 0;
	if (b < 0)
	b = 0;
	return(r * 65536 + g * 256 + b);
}
int main(int argc, char **argv)
{
	int     res_x;  // faire une struct coord avec tt les x et y
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
	float c;   /////////faire une struct avec tt la merde couleur affichage
	t_vec normal;
	t_vec light;
	t_vec point;

	fov = ft_atoi(argv[3]);
	res_x = ft_atoi(argv[1]);
	res_y = ft_atoi(argv[2]);
	ray.z = 623.5;
	center.x = 0;
	center.y = 0;
	center.z = -10;
	origin.x = 0;
	origin.y = 0;
	origin.z = 0;

	t_light l1;
	l1.pos.x = -5;
	l1.pos.y = -5;
	l1.pos.z = -5;
	l1.col.r = 255;
	l1.col.g = 0;
	l1.col.b = 0;
	t_light l2;
	l2.pos.x = 5;
	l2.pos.y = 5;
	l2.pos.z = -5;
	l2.col.r = 0;
	l2.col.g = 0;
	l2.col.b = 255;
	l2.next = NULL;
	l1.next = &l2;

	t_col back;
	back.r = 0;
	back.g = 0;
	back.b = 0;

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
				t_col color;
				color.r = 0;
				color.g = 0;
				color.b = 0;
				if (dist == -1)
					color = back;
				else
				{
					t_light *la;
					la = &l1;
					while (la != NULL)
					{
						point = plus(origin, fois(ray, dist));
						light = normalize(min(la->pos, point));
						normal = normalize(min(point, center));
						c = dot(light, normal);
						color.r += c * la->col.r;
						color.g += c * la->col.g;
						color.b += c * la->col.b;
						la = la->next;
					}
				}
				mlx_pixel_put(mlx_ptr, mlx_win, x, y, rgbtoon(color.r, color.g, color.b));
				y++;
			}
			x++;
		}

	mlx_hook(mlx_win, DestroyNotify, StructureNotifyMask, exit_hook, r);
	mlx_key_hook(mlx_win, &key_hook, r);
	mlx_loop(mlx_ptr);
}
