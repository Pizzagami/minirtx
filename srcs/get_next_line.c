/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 15:03:19 by selgrabl          #+#    #+#             */
/*   Updated: 2019/12/09 15:24:54 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

char	**init(char **line, char **buf, int fd)
{
	int x;

	if (!(*line = malloc(sizeof(char))))
		return (NULL);
	(*line)[0] = 0;
	if (!buf)
	{
		if (!(buf = malloc(sizeof(char *) * 10240)))
			return (NULL);
		x = 0;
		while (x < 10240)
		{
			buf[x] = NULL;
			x++;
		}
	}
	if (buf[fd] == NULL)
	{
		if (!(buf[fd] = malloc(sizeof(char) * (50 + 1))))
			return (NULL);
		buf[fd][0] = 0;
	}
	return (buf);
}

int		get_next_line(int fd, char **line)
{
	static char		**buf;
	int				x;

	if (50 < 1 || line == 0 || fd < 0)
		return (-1);
	buf = init(line, buf, fd);
	while (1)
	{
		x = -1;
		if (buf[fd][0] == 0)
		{
			while (x++ < 50)
				buf[fd][x] = 0;
			x = read(fd, buf[fd], 50);
			if (x < 1)
				return (clear_buff(x, fd, &buf));
		}
		x = 0;
		while (buf[fd][x] && buf[fd][x] != '\n')
			x++;
		join2(line, &buf[fd], x);
		if (buf[fd][0] == '\n')
			return (increase_buf(&buf[fd]));
	}
}

int		increase_buf(char **buf)
{
	int x;

	x = 0;
	while ((*buf)[x])
	{
		(*buf)[x] = (*buf)[x + 1];
		x++;
	}
	return (1);
}

void	join2(char **line, char **buf, int x)
{
	int		i;
	int		j;
	int		a;
	char	*tmp;

	a = 0;
	i = (*line) ? ft_strlen(*line) : 0;
	j = x;
	tmp = *line;
	if (!(*line = malloc(sizeof(char) * (i + j + 1))))
		exit(0);
	while (a < i)
	{
		(*line)[a] = tmp[a];
		a++;
	}
	free(tmp);
	a = -1;
	while (++a < j)
		(*line)[i + a] = (*buf)[a];
	(*line)[i + j] = '\0';
	while (a--)
		increase_buf(buf);
}

int		clear_buff(int x, int fd, char ***buf)
{
	char	**buff;
	int		i;

	buff = *buf;
	i = 0;
	free(buff[fd]);
	buff[fd] = NULL;
	while (i < 10240 && buff && buff[i] == NULL)
		i++;
	if (i == 10240 && buff != NULL)
	{
		free(*buf);
		*buf = NULL;
	}
	return ((x == 0) ? 0 : -1);
}
