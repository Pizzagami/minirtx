/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 15:25:43 by selgrabl          #+#    #+#             */
/*   Updated: 2019/12/02 18:09:23 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int main(int argc, char **argv)
{
	parseke(argv[1]);
	printf("=====PARSING DONE=====\n");
	return (0);
}

t_rtx		parseke(char *str)
{
	t_rtx	rtx;
	int		fd;
	
	fd = open(str, O_RDONLY);
	if (fd < 0)
	{
		perror("Error : ");
		exit(1);
	}
	while(*(str + 1))
		str++;
	if ((*str) != 't' || *(str - 1) != 'r' || *(str - 2) != '.')
	{
		printf("Error : Format incorrect \n");
		close(fd);
		exit(1);
	}
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

	x = 0;
	while(buf[x])
	{
		if(buf[x] == '\n')
			x++;
		if (buf[x] == 'A' || buf[x] == 'R')
			err = init_ar(buf, &x, rtx);
		if(buf[x] == 'l' || (buf[x] == 'c' && buf[x + 1] != 'y'))
			err = init_view(buf, &x, rtx);
		if (buf[x] == 's' || (buf[x] == 'p' && buf[x + 1] == 'l'))
			err =init_sp(buf, &x, rtx);
		if(buf[x] == 't' || (buf[x] == 'c' && buf[x + 1] == 'y'))
			err =init_tc(buf, &x, rtx);
		if (err != NULL)
		{
			write(2, err, ft_strlen(err));
			close(fd);
			printf("=====Exit programme because of parsing error=====\n");
			exit(1);
		}
		x++;
	}
}