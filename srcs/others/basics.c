/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 09:49:19 by braimbau          #+#    #+#             */
/*   Updated: 2020/02/05 13:31:37 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

int		ft_strlen(char *str)
{
	int i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*strjoin(int nbr, char *s1, ...)
{
	char *str;

	va_list(ap);
	va_start(ap, s1);
	str = s1;
	while (nbr > 2)
	{
		str = join(str, va_arg(ap, char *));
		nbr--;
	}
	va_end(ap);
	return (str);
}

char	*join(char *s1, char *s2)
{
	int		i;
	int		n;
	char	*r;

	if (ft_strlen(s1) + ft_strlen(s2) == 0)
		return (NULL);
	if (!(r = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	i = 0;
	n = 0;
	while (s1 != NULL && s1[i])
	{
		r[i] = s1[i];
		i++;
	}
	while (s2 != NULL && s2[n])
	{
		r[i + n] = s2[n];
		n++;
	}
	r[i + n] = 0;
	return (r);
}

int		ft_strcmp(char *s1, char *s2)
{
	unsigned int i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - s2[i]);
		i++;
	}
	if (((s1[i] == '\0' && s2[i] != '\0') ||
				(s2[i] == '\0' && s1[i] != '\0')))
		return ((unsigned char)s1[i] - s2[i]);
	return (0);
}
