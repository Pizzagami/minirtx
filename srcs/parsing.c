/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 15:25:43 by selgrabl          #+#    #+#             */
/*   Updated: 2019/12/07 18:44:18 by braimbau         ###   ########.fr       */
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
		write(1, "Error : too many argunens\n", 26);
	rtx = parsing(fd);
	close(fd);
	return(rtx);
}

t_rtx		parsing(int fd)
{
	t_rtx	rtx;
	char	buf[BUFFER_SIZE];


	rtx.res.x = -1;
	rtx.amb.color.b = -1;
	init_lst(fd,&rtx);
	if(read(fd, &buf, BUFFER_SIZE) == BUFFER_SIZE)
	{
		printf("Error : CE SERAI UN PEU LONG KAN MEME !!\n");
		exit(1);
	}
	ft_switch(buf, &rtx, fd);
	printf("=====PARSING ALMOSTE DONE=====\n");
	if (rtx.res.x < 0 || rtx.amb.color.b < 0)
	{
		write(2 , "Error : Resolution or/and Ambiant light undefined", 49);
		close(fd);
		exit(EXIT_FAILURE);
	}
	return(rtx);
}

void		ft_switch(char buf[BUFFER_SIZE], t_rtx *rtx, int fd)
{
	
	int x;
	char *err;

	err =NULL;
	x = 0;
	while(buf[x])
	{
		if(buf[x] == '\n')
			x++;
		if (buf[x] == 'A' || buf[x] == 'R')
			err = init_ar(buf, &x, rtx);
		else if(buf[x] == 'l' || (buf[x] == 'c' && buf[x + 1] != 'y'))
			err = init_view(buf, &x, rtx);
		else if (buf[x] == 's' || (buf[x] == 'p' && buf[x + 1] == 'l'))
			err = init_sp(buf, &x, rtx);
		else if(buf[x] == 't' || (buf[x] == 'c' && buf[x + 1] == 'y'))
			err = init_tc(buf, &x, rtx);
		while (buf[x] == ' ')
			x++;
		if (err != NULL || (buf[x] != '\n' && buf[x]))
		{
			if (err != NULL)
				write(2, err, ft_strlen(err));
			else
				write(1, "Error : format of file is incorect\n", 35);
			close(fd);
			printf("=====Exit programme because of parsing error=====\n");
			exit(1);
		}
		x++;
	}
}
