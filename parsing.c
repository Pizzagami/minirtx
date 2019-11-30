/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 15:25:43 by selgrabl          #+#    #+#             */
/*   Updated: 2019/11/30 18:04:11 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

t_rtx		parseke(char *str)
{
	t_rtx	rtx;
	int		fd;
	
	fd = open(str, O_RDONLY);
	if (fd < 0)
	{
		perror("");
		exit(1);
	}
	printf("|%d|\n", fd);
	while(*(str + 1))
		str++;
	if ((*str) != 't' || *(str - 1) != 'r' || *(str - 2) != '.')
	{
		printf("Format incorrect \n");
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
	int		x;
	char	buf[BUFFER_SIZE];

	if(read(fd, &buf, BUFFER_SIZE) == BUFFER_SIZE)
	{
		printf("CE SERAI UN PEU LONG KAN MEME !!\n");
		exit(1);
	}
	x = 0;
	while(buf[x])
	{
		if(buf[x] == '\n')
			x++;
		if(buf[x] == 'A' || buf[x] == 'R')
			init_ar(buf, &x, &rtx);
		if(buf[x] == 'l' || (buf[x] == 'c' && buf[x + 1] != 'y'))
			init_view(buf, &x, &rtx);
		if (buf[x] == 's' || (buf[x] == 'p' && buf[x + 1] == 'l'))
			init_sp(buf, &x, &rtx);
		if(buf[x] == 't' || (buf[x] == 'c' && buf[x + 1] == 'y'))
			init_tc(buf, &x, &rtx);
			printf("|%f|\n", NAF);
	}
	return(rtx);
}