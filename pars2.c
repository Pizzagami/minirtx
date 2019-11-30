/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:07:13 by selgrabl          #+#    #+#             */
/*   Updated: 2019/11/30 18:37:49 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

char *init_ar(char buf[BUFFER_SIZE], int *x, t_rtx *rtx)
{
	if (buf[*x] == 'A')
	{
		rtx->amb.ratio = read_float(buf, x);
		if (rtx->amb.ratio == NAF)
			return ("Error : Invalid float for ratio of ambiant light\n");
		if (rtx->amb.ratio > 1 || rtx->amb.ratio < 0)
			return ("Error : Value out of range for ratio of ambiant light\n");
		rtx->amb.color.r = read_int(buf, x);
		if (rtx->amb.ratio == NaN)
			return ("Error : Invalid integer for red of ambiant light\n");
		if (rtx->amb.color.r> 255 || rtx->amb.color.r < 0)
			return ("Error : Value out of range for ratio of ambiant light\n");
		if (buf[*x] != ',')
			return ("Error : Invalid forma for ambiant light\n")
		x++;
		
}

void init_view(char buf[BUFFER_SIZE], int *x, t_rtx *rtx)
{

}

void init_sp(char buf[BUFFER_SIZE], int *x, t_rtx *rtx)
{

}

void init_tc(char buf[BUFFER_SIZE], int *x, t_rtx *rtx)
{
	
}

float read_float(char buf[BUFFER_SIZE], int *x)
{
	float ret;

	while (buf[*x] == ' ')
		*x++;
	ret = ft_atof(buf[BUFFER_SIZE], x);	
	if (ret > max || ret < min)
		ret = NAF;
	while ((buf[*x] >= '0' && buf[*x] <= '9') || buf[*x] == '-' || buf[*x] == '.')
		*x++;
	while (buf[*x] == ' ')
		*x++;
}

int read_int(char buf[BUFFER_SIZE], int *x)
{
	int ret;

	while (buf[*x] == ' ')
		*x++;
	ret = ft_atoi(buf[BUFFER_SIZE], x);	
	if (ret > max || ret < min)
		ret = NAF;
	while ((buf[*x] >= '0' && buf[*x] <= '9') || buf[*x] == '-' || buf[*x] == '.')
		*x++;
}