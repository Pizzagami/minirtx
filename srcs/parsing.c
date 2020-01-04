/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 15:25:43 by selgrabl          #+#    #+#             */
/*   Updated: 2020/01/04 19:55:19 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_rtx		parseke(int argc, char **argv)
{
	t_rtx	rtx;
	int		fd;
	
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Error : ");
		exit(1);
	}
	while(*(argv[1] + 1))
		argv[1]++;
	if ((*argv[1] != 't' || *(argv[1] - 1) != 'r' || *(argv[1] - 2) != '.'))
	{
		printf("Error : Format incorrect \n");
		close(fd);
		exit(1);
	}
	if (argc == 3)
		rtx.save = (ft_strcmp(argv[2],"-save") == 0) ? 1 : 0;
	else if (argc > 3)
		write(1, "Error : too many arguments\n", 30);
	rtx = parsing(fd);
	close(fd);
	return(rtx);
}

t_rtx		parsing(int fd)
{
	t_rtx	rtx;
	char *str;
	int i;
	
	i = 0;
	rtx.res.x = -1;
	rtx.amb.color.b = -1;
	init_lst(&rtx);
	while (get_next_line(fd, &str) != 0)
	{
		ft_switch(str, &rtx, fd, i);
		i++;
	}
	ft_switch(str, &rtx, fd, i);
	if (rtx.res.x < 0 || rtx.amb.color.b < 0)
	{
		write(2 , "Error : Resolution or/and Ambiant light undefined\n", 50);
		close(fd);
		exit(EXIT_FAILURE);
	}
	return(rtx);
}

void		ft_switch(char *str, t_rtx *rtx, int fd, int i)
{	
	char *err;
	char **buf;

	if (str[0] == '\0')
		return;
	err = NULL;
	buf = ft_split(str, " ");
	err = (ft_strcmp(buf[0], "A") == 0) ? pars_a(buf, rtx) : err;
	err = (ft_strcmp(buf[0], "R") == 0) ? pars_r(buf, rtx) : err;
	err = (ft_strcmp(buf[0], "c") == 0) ? pars_c(buf, rtx) : err;
	err = (ft_strcmp(buf[0], "l") == 0) ? pars_l(buf, rtx) : err;
	err = (ft_strcmp(buf[0], "sp") == 0) ? pars_s(buf, rtx) : err;
	err = (ft_strcmp(buf[0], "sq") == 0) ? pars_sq(buf, rtx) : err;
	err = (ft_strcmp(buf[0], "tr") == 0) ? pars_tr(buf, rtx) : err;
	err = (ft_strcmp(buf[0], "cy") == 0) ? pars_cy(buf, rtx) : err;
	err = (ft_strcmp(buf[0], "cu") == 0) ? pars_cu(buf, rtx) : err;
	err = (ft_strcmp(buf[0], "py") == 0) ? pars_py(buf, rtx) : err;
	err = (ft_strcmp(buf[0], "ce") == 0) ? pars_ce(buf, rtx) : err;
	err = (ft_strcmp(buf[0], "pl") == 0) ? pars_pl(buf, rtx) : err;
	err = join(err, check_ligne(str));
	if (err)
	{
		ft_putstr(join(err, " (line : "));
		ft_putnbr(i + 1);
		ft_putstr(")\n");
		close(fd);
		exit(EXIT_FAILURE);
	}
}

int main2(int argc, char **argv)
{
	t_rtx 	rtx;
	int		i;
	t_cam	*cam;
	t_light	*light;
	t_tg	*shape;

	rtx = parseke(argc, argv);
	printf("amb : ratio : %5f color : %3d %3d %3d \n", rtx.amb.ratio, rtx.amb.color.r, rtx.amb.color.g, rtx.amb.color.b);
	i = 0;
	cam = rtx.cam;
	while(cam)
	{
		i++;
		printf("cam %d : pos : %3f %3f %3f vec : %3f %3f %3f fov = %d\n", i, cam->origin.x, cam->origin.y, cam->origin.z, cam->vec.x, cam->vec.y, cam->vec.z, cam->fov);
		cam = cam->next;
	}
	i = 0;
	light = rtx.light;
	while(light)
	{
		i++;
		printf("light %d : pos : %3f %3f %3f ratio : %f color : %d %d %d\n", i, light->pos.x, light->pos.y, light->pos.z, light->ratio, light->color.r, light->color.g, light->color.b);
		light = light->next;
	}
	i = 0;
	shape = rtx.shape;
	while(shape)
	{
		i++;
		if (shape->type == 4)
			printf("shape %d : square : pos : %f %f %f vec : %f %f %f hight : %f color : %d %d %d\n", i, shape->center.x, shape->center.y, shape->center.z, shape->vec.x, shape->vec.y, shape->vec.z, shape->hi, shape->color.r, shape->color.g, shape->color.b);
		if (shape->type == 2)
			printf("shape %d : cylinder : pos : %f %f %f vec : %f %f %f hight : %f dia = %f color : %d %d %d\n", i, shape->center.x, shape->center.y, shape->center.z, shape->vec.x, shape->vec.y, shape->vec.z, shape->hi, shape->dia, shape->color.r, shape->color.g, shape->color.b);
		if (shape->type == 0)
			printf("shape %d : plane : pos : %f %f %f vec : %f %f %f color : %d %d %d\n", i, shape->center.x, shape->center.y, shape->center.z, shape->vec.x, shape->vec.y, shape->vec.z, shape->color.r, shape->color.g, shape->color.b);
		shape = shape->next;

	}
	return (0);
}

void	corners(t_tg *shape)
{
	//FAUX
	shape->hi /= 2;
	shape->p1.x = shape->hi * (shape->v1.x + shape->v2.x) + shape->center.x;
	shape->p1.y = shape->hi * (shape->v1.y + shape->v2.y) + shape->center.y;
	shape->p1.z = shape->hi * (shape->v1.z + shape->v2.z) + shape->center.z;
	shape->p2.x = shape->hi * (shape->v1.x - shape->v2.x) + shape->center.x;
	shape->p2.y = shape->hi * (shape->v1.y - shape->v2.y) + shape->center.y;
	shape->p2.z = shape->hi * (shape->v1.z - shape->v2.z) + shape->center.z;
	shape->p3.x = shape->hi * -(shape->v1.x + shape->v2.x) + shape->center.x;
	shape->p3.y = shape->hi * -(shape->v1.y + shape->v2.y) + shape->center.y;
	shape->p3.z = shape->hi * -(shape->v1.z + shape->v2.z) + shape->center.z;
	shape->p4.x = shape->hi * (-shape->v1.x + shape->v2.x) + shape->center.x;
	shape->p4.y = shape->hi * (-shape->v1.y + shape->v2.y) + shape->center.y;
	shape->p4.z = shape->hi * (-shape->v1.z + shape->v2.z) + shape->center.z;
	/*shape->p1.x = (sqrt(pow(2,shape->hi * shape->v1.x) + pow(2,shape->hi * shape->v2.x))) + shape->center.x;
	shape->p1.y = (sqrt(pow(2,shape->hi * shape->v1.y) + pow(2,shape->hi * shape->v2.y))) + shape->center.y;
	shape->p1.z = (sqrt(pow(2,shape->hi * shape->v1.z) + pow(2,shape->hi * shape->v2.z))) + shape->center.z;
	shape->p2.x = (sqrt(pow(2,shape->hi * shape->v1.x) - pow(2,shape->hi * shape->v2.x))) + shape->center.x;
	shape->p2.y = (sqrt(pow(2,shape->hi * shape->v1.y) - pow(2,shape->hi * shape->v2.y))) + shape->center.y;
	shape->p2.z = (sqrt(pow(2,shape->hi * shape->v1.z) - pow(2,shape->hi * shape->v2.z))) + shape->center.z;
	shape->p3.x = (-sqrt(pow(2,shape->hi * shape->v1.x) + pow(2,shape->hi * shape->v2.x))) + shape->center.x;
	shape->p3.y = (-sqrt(pow(2,shape->hi * shape->v1.y) + pow(2,shape->hi * shape->v2.y))) + shape->center.y;
	shape->p3.z = (-sqrt(pow(2,shape->hi * shape->v1.z) + pow(2,shape->hi * shape->v2.z))) + shape->center.z;
	shape->p4.x = (sqrt(-pow(2,shape->hi * shape->v1.x) + pow(2,shape->hi * shape->v2.x))) + shape->center.x;
	shape->p4.y = (sqrt(-pow(2,shape->hi * shape->v1.y) + pow(2,shape->hi * shape->v2.y))) + shape->center.y;
	shape->p4.z = (sqrt(-pow(2,shape->hi * shape->v1.z) + pow(2,shape->hi * shape->v2.z))) + shape->center.z;*/
}

void	find_vecs(t_tg *shape)
{
if (fabsf(shape->vec.x) >= fabsf(shape->vec.y) &&
		(fabsf(shape->vec.x) >= fabsf(shape->vec.z)))
	{
		shape->v1.x = 1;
		shape->v1.y = 0;
		shape->v1.z = (shape->vec.z != 0)? -shape->vec.x / shape->vec.z : 0;
	}
	else if (fabsf(shape->vec.z) >= fabsf(shape->vec.y) &&
		(fabsf(shape->vec.z) >= fabsf(shape->vec.x)))
	{
		shape->v1.z = 1;
		shape->v1.y = 0;
		shape->v1.x = (shape->vec.x != 0)? -shape->vec.z / shape->vec.x : 0;
	}
	else if (fabsf(shape->vec.y) >= fabsf(shape->vec.x) &&
		(fabsf(shape->vec.x) >= fabsf(shape->vec.z)))
	{
		shape->v1.y = 1;
		shape->v1.x = 0;
		shape->v1.z = (shape->vec.z != 0)? -shape->vec.y / shape->vec.z : 0;
	}
	shape->v1 = normalize(shape->v1);
	shape->v2 = normalize(cross(shape->vec, shape->v1));
	tri_vecs(shape);
}