/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:07:13 by selgrabl          #+#    #+#             */
/*   Updated: 2019/12/01 20:04:40 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char *init_ar(char buf[BUFFER_SIZE], int *x, t_rtx *rtx)
{
	if (buf[*x] == 'A')
	{
		(*x)++;
		read_float(buf, x, &(rtx->amb.ratio));
		if (rtx->amb.ratio == NAF)
			return("Error : Invalid float for ratio of ambiant light\n");
		if (rtx->amb.ratio > 1 || rtx->amb.ratio < 0)
			return("Error : Value out of range for ratio of ambiant light\n");
		return(check_color(buf, x, &(rtx->amb.color), "ambiante light\n"));
	}
	read_int(buf, x, &(rtx->res.x));
	if (rtx->res.x > 2160 || rtx->res.x < 0)
		return ("Error : Value out of range for resolution in \"x\"\n");
	read_int(buf, x, &(rtx->res.y));
	if (rtx->res.y > 1440 || rtx->res.y < 0)
		return ("Error : Value out of range for resolution in \"y\"\n");
	return(NULL);
}

char *init_view(char buf[BUFFER_SIZE], int *x, t_rtx *rtx)
{
	return(NULL);
}

char *init_sp(char buf[BUFFER_SIZE], int *x, t_rtx *rtx)
{
	char *ret;
	t_tg *shape;

	shape = last_tg(rtx->shape);
	if (buf[*x] == 's' && buf[*x + 1] == 'p')
	{
		shape->type = 1;
		ret = check_pos(buf, x, &(shape->vec), "vector of sphere");
		read_float(buf, x, &(shape->dia));
		if (shape->dia < 0)
			return ("Error : diameter must be positive\n");
		(*x)++;
		ret = join(ret, check_color(buf, x, &(shape->color), "for the sphere"));
		return (ret);
	}
	shape->type = (buf[*x] == 's') ? 4 : 0;
	ret = check_pos(buf, x, &(shape->vec), "vector of plane / square)");
	(shape->type == 4) ? read_float(buf, x, &(shape->hi)): 0;
	if (shape->hi < 0)
			return ("Error : height must be positive\n");
			(*x)++;
	ret = join(ret, check_color(buf, x, &(shape->color), "for plane / square"));
	return (ret);
}

char *init_tc(char buf[BUFFER_SIZE], int *x, t_rtx *rtx)
{
	return (NULL);
}
