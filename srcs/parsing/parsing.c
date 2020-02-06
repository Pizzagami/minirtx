/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 15:25:43 by selgrabl          #+#    #+#             */
/*   Updated: 2020/02/06 15:58:36 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

t_rtx		parseke(int argc, char **argv, void *mlx_ptr)
{
	t_rtx	rtx;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Error : ");
		exit(1);
	}
	while (*(argv[1] + 1))
		argv[1]++;
	if ((*argv[1] != 't' || *(argv[1] - 1) != 'r' || *(argv[1] - 2) != '.'))
		exit_error(fd);
	if (argc > 3)
		write(1, "Error : too many arguments\n", 30);
	if ((argc == 3) && (ft_strcmp(argv[2], "-save") != 0))
		exit_error(fd);
	rtx = parsing(fd, mlx_ptr);
	rtx.save = 0;
	if (argc == 3)
		rtx.save = (ft_strcmp(argv[2], "-save") == 0) ? 1 : 0;
	close(fd);
	return (rtx);
}

t_rtx		parsing(int fd, void *mlx_ptr)
{
	t_rtx	rtx;
	char	*str;
	int		i;

	i = 0;
	rtx.mlx_ptr = mlx_ptr;
	rtx.res.x = -1;
	rtx.amb.color.b = -1;
	init_lst(&rtx);
	while (get_next_line(fd, &str) != 0)
	{
		ft_switch(str, &rtx, fd, i);
		free(str);
		i++;
	}
	ft_switch(str, &rtx, fd, i);
	free(str);
	if (rtx.res.x < 0 || rtx.amb.color.b < 0 || rtx.cam == NULL)
	{
		write(2, "Error : Missing Ambiant Light, Camera or Resolution\n", 52);
		close(fd);
		exit(EXIT_FAILURE);
	}
	return (rtx);
}

static char	*check_ligne(char *str)
{
	int i;

	i = 1;
	while (str[i])
	{
		if (str[i] == ',' && str[i - 1] == ',')
			return ("Invalid line format");
		i++;
	}
	return (NULL);
}

static char	*monster(char **buf, t_rtx *rtx)
{
	char *err;

	err = NULL;
	err = (ft_strcmp(buf[0], "A") == 0) ? pars_a(buf, rtx) : err;
	err = (ft_strcmp(buf[0], "R") == 0) ? pars_r(buf, rtx) : err;
	err = (ft_strcmp(buf[0], "c") == 0) ? pars_c(buf, rtx) : err;
	err = (ft_strcmp(buf[0], "l") == 0) ? pars_l(buf, rtx) : err;
	err = (ft_strcmp(buf[0], "sp") == 0) ? pars_s(buf, rtx) : err;
	err = (ft_strcmp(buf[0], "sm") == 0) ? pars_sm(buf, rtx) : err;
	err = (ft_strcmp(buf[0], "sq") == 0) ? pars_sq(buf, rtx) : err;
	err = (ft_strcmp(buf[0], "tr") == 0) ? pars_tr(buf, rtx) : err;
	err = (ft_strcmp(buf[0], "cy") == 0) ? pars_cy(buf, rtx) : err;
	err = (ft_strcmp(buf[0], "cu") == 0) ? pars_cu(buf, rtx) : err;
	err = (ft_strcmp(buf[0], "sa") == 0) ? pars_sa(buf, rtx) : err;
	err = (ft_strcmp(buf[0], "co") == 0) ? pars_co(buf, rtx) : err;
	err = (ft_strcmp(buf[0], "py") == 0) ? pars_py(buf, rtx) : err;
	err = (ft_strcmp(buf[0], "ce") == 0) ? pars_ce(buf, rtx) : err;
	err = (ft_strcmp(buf[0], "pl") == 0) ? pars_pl(buf, rtx) : err;
	err = (ft_strcmp(buf[0], "AA") == 0) ? pars_aa(buf, rtx) : err;
	return (err);
}

void		ft_switch(char *str, t_rtx *rtx, int fd, int i)
{
	char *err;
	char **buf;

	buf = ft_split(str, " ");
	if (str[0] == '\0')
	{
		free(buf);
		return ;
	}
	if (buf[0] == NULL)
		return ;
	err = monster(buf, rtx);
	free_buf(buf);
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
