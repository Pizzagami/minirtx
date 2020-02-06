/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 10:34:04 by selgrabl          #+#    #+#             */
/*   Updated: 2020/02/06 15:57:14 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

void		write_number_in_file(int nb, int fd)
{
	write(fd, &nb, sizeof(int));
}

static void	write_header(int fd, t_res res)
{
	write(fd, "BM", 2);
	write_number_in_file(54 + 4 * res.x * res.y, fd);
	write_number_in_file(0, fd);
	write_number_in_file(54, fd);
	write_number_in_file(40, fd);
	write_number_in_file(res.x, fd);
	write_number_in_file(res.y, fd);
	write_number_in_file(2097153, fd);
	write_number_in_file(0, fd);
	write_number_in_file(0, fd);
	write_number_in_file(0, fd);
	write_number_in_file(0, fd);
	write_number_in_file(0, fd);
	write_number_in_file(0, fd);
}

void		export_to_bmp(char *id, t_res res)
{
	int		fd;
	char	c;
	int		y;
	int		x;

	fd = open("./file.bmp", O_CREAT | O_WRONLY, 777);
	write_header(fd, res);
	y = res.y - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < res.x)
		{
			c = id[(y * res.x + x) * 4];
			write(fd, &c, 1);
			c = id[(y * res.x + x) * 4 + 1];
			write(fd, &c, 1);
			c = id[(y * res.x + x) * 4 + 2];
			write(fd, &c, 1);
			c = (char)255;
			write(fd, &c, 1);
			x++;
		}
		y--;
	}
}

void		put_pixel(t_res r, char **id, int sl, t_color color)
{
	(*id)[(r.x + (r.y * sl)) * 4] = (char)color.b;
	(*id)[((r.x + (r.y * sl)) * 4) + 1] = (char)color.g;
	(*id)[((r.x + (r.y * sl)) * 4) + 2] = (char)color.r;
}

t_color		cp(int x, int y, char *id, t_res res)
{
	t_color color;

	color.r = id[(x + y * res.x) * 4 + 2];
	color.g = id[(x + y * res.x) * 4 + 1];
	color.b = id[(x + y * res.x) * 4];
	return (color);
}
