/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 17:26:19 by braimbau          #+#    #+#             */
/*   Updated: 2020/01/28 16:44:12 by raimbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

void	create_tri(t_vec p1, t_vec p2, t_vec p3, t_rtx *rtx)
{
	t_tg *shape;
	t_tg tmp;

	tmp = *(rtx->shape);
	shape = malloc(sizeof(t_tg));
	shape->next = rtx->shape;
	rtx->shape = shape;
	rtx->shape->type = 3;
	rtx->shape->trans = tmp.trans;
	rtx->shape->refl = tmp.refl;
	rtx->shape->color = tmp.color;
	rtx->shape->p1 = p1;
	rtx->shape->p2 = p2;
	rtx->shape->p3 = p3;
	shape->normal = normalize(cross(min(shape->p2, shape->p1),
		min(shape->p3, shape->p1)));
	shape->center = shape->p1;
}

void	write_number_in_file(int nb, int fd)
{
	write(fd, &nb, sizeof(int));
}

void		write_header(int fd, t_res res)
{
	write(fd, "BM", 2); //identifier
	write_number_in_file(54 + 4 * res.x * res.y, fd); //size of file
	write_number_in_file(0, fd); //reserved
	write_number_in_file(54, fd); // offset
	write_number_in_file(40, fd); //size of image header
	write_number_in_file(res.x, fd); //width of image
	write_number_in_file(res.y, fd); //height of image
	write_number_in_file(2097153, fd); //plans + nb bits/pix
	write_number_in_file(0, fd); //compression
	write_number_in_file(0, fd); //size of image
	write_number_in_file(0, fd); // resolution x
	write_number_in_file(0, fd); // resolution y
	write_number_in_file(0, fd); //nb colors
	write_number_in_file(0, fd); //nb important colors

}

void		export_to_bmp(char *id, t_res res)
{
	int		fd;
	char	full;
	int		y;
	int		x;

	full = (char)255;
	fd = open("./file.bmp", O_CREAT | O_WRONLY, 777);
	write_header(fd, res);
	y = res.y - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < res.x)
		{
			write(fd, &id[(y * res.x + x) * 4], 1);
			write(fd, &id[(y * res.x + x) * 4 + 1], 1);
			write(fd, &id[(y * res.x + x) * 4 + 2], 1);
			write(fd, &full, 1);
			x++;
		}
		y--;
	}
}

void	make_mapping(t_tg *shape)
{
	float u;
	float v;
	float theta;

	if (shape->type != 11)
		return;
	v = acos(-dot(shape->v1, shape->normal)) / M_PI;
	theta = (acos(dot(shape->normal, shape->v2) / sin(acos(-dot(shape->v1, shape->normal))))) / (2 * M_PI);
	if (dot(cross(shape->v1, shape->v2), shape->normal) > 0)
		u = theta;
	else
		u = 1 - theta;
	shape->color = cp(u * shape->map_res.x, v * shape->map_res.y, shape->map_id, shape->map_res);
	shape->color.r = (unsigned char)shape->color.r;
	shape->color.g = (unsigned char)shape->color.g;
	shape->color.b = (unsigned char)shape->color.b;
}

