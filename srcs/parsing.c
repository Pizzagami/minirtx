/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 15:25:43 by selgrabl          #+#    #+#             */
/*   Updated: 2020/01/23 15:53:36 by selgrabl         ###   ########.fr       */
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

	err = NULL;
	buf = ft_split(str, " ");
	if (str[0] == '\0')
		return;
	err = (ft_strcmp(buf[0], "A") == 0) ? pars_a(buf, rtx) : err;
	err = (ft_strcmp(buf[0], "R") == 0) ? pars_r(buf, rtx) : err;
	err = (ft_strcmp(buf[0], "c") == 0) ? pars_c(buf, rtx) : err;
	err = (ft_strcmp(buf[0], "l") == 0) ? pars_l(buf, rtx) : err;
	err = (ft_strcmp(buf[0], "sp") == 0) ? pars_s(buf, rtx) : err;
	err = (ft_strcmp(buf[0], "sq") == 0) ? pars_sq(buf, rtx) : err;
	err = (ft_strcmp(buf[0], "tr") == 0) ? pars_tr(buf, rtx) : err;
	err = (ft_strcmp(buf[0], "cy") == 0) ? pars_cy(buf, rtx) : err;
	err = (ft_strcmp(buf[0], "cu") == 0) ? pars_cu(buf, rtx) : err;
	err = (ft_strcmp(buf[0], "sa") == 0) ? pars_sa(buf, rtx) : err;
	err = (ft_strcmp(buf[0], "co") == 0) ? pars_co(buf, rtx) : err;
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

void	corners(t_tg *shape)
{
	shape->hi /= 2;
	shape->p1 = plus(fois(plus(shape->v1,shape->v2),shape->hi),shape->center);
	shape->p2 = plus(fois(min(shape->v1,shape->v2),shape->hi),shape->center);
	shape->p3 = plus(fois(plus(shape->v1,shape->v2),-shape->hi),shape->center);
	shape->p4 = plus(fois(min(shape->v2,shape->v1),shape->hi),shape->center);

	shape->hi *= 2;
}

void	find_vecs(t_tg *shape)
{
	if (fabsf(shape->vec.x) <= fabsf(shape->vec.y) &&
		(fabsf(shape->vec.x) <= fabsf(shape->vec.z)))
	{
		shape->v1.x = 1;
		shape->v1.y = 0;
		shape->v1.z = (shape->vec.z != 0)? -shape->vec.x / shape->vec.z : 0;
	}
	else if (fabsf(shape->vec.z) <= fabsf(shape->vec.y) &&
		(fabsf(shape->vec.z) <= fabsf(shape->vec.x)))
	{
		shape->v1.z = 1;
		shape->v1.y = 0;
		shape->v1.x = (shape->vec.x != 0)? -shape->vec.z / shape->vec.x : 0;
	}
	else if (fabsf(shape->vec.y) <= fabsf(shape->vec.x) &&
		(fabsf(shape->vec.x) <= fabsf(shape->vec.z)))
	{
		shape->v1.y = 1;
		shape->v1.x = 0;
		shape->v1.z = (shape->vec.z != 0)? -shape->vec.y / shape->vec.z : 0;
	}
	shape->v1 = normalize(shape->v1);
	shape->v2 = normalize(cross(shape->vec, shape->v1));
}
