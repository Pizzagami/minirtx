/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:07:13 by selgrabl          #+#    #+#             */
/*   Updated: 2019/12/03 15:54:30 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char *init_ar(char buf[BUFFER_SIZE], int *x, t_rtx *rtx)
{
	(*x)++;
	if (buf[(*x) - 1] == 'A')
	{
		rtx->amb.ratio = read_float(buf, x);
		if (rtx->amb.ratio == NAF)
			return("Error : Invalid float for ratio of ambiant light\n");
		if (rtx->amb.ratio > 1 || rtx->amb.ratio < 0)
			return("Error : Value out of range for ratio of ambiant light\n");
		return(check_color(buf, x, &(rtx->amb.color), "ambiante light\n"));
	}
	rtx->res.x = read_int(buf, x);
	if (rtx->res.x > 2160 || rtx->res.x < 1)
		return ("Error : Value out of range for resolution in \"x\"\n");
	rtx->res.y = read_int(buf, x);
	if (rtx->res.y > 1440 || rtx->res.y < 1)
		return ("Error : Value out of range for resolution in \"y\"\n");
	return(NULL);
}

char *init_view(char buf[BUFFER_SIZE], int *x, t_rtx *rtx)
{
	char *ret;
	t_cam *cam;
	
	(*x) += 2;
	if (buf[*x - 2] == 'c' && buf[*x - 1] == ' ')
	{
		(*x)++;
		cam = last_cam(rtx->cam);
		cam->next = NULL;
		ret = check_pos(buf, x, &(cam->origin), "position of camera\n");
		ret = join(ret, check_vec(buf, x, &(cam->vec), "vector of camera\n"));
		cam->fov = read_int(buf, x);
		if (cam->fov < 0 || cam->fov > 180 || cam->fov == NAF)
			return ("Error : Invalid float for field of view\n");
		return (ret);
	}
	return(ret);
}

char *init_sp(char buf[BUFFER_SIZE], int *x, t_rtx *rtx)
{
	char *ret;
	t_tg *shape;

	shape = malloc(sizeof(t_tg));
	shape->next = rtx->shape;
	rtx->shape = shape;
	(*x) += 2 ;
	if (buf[*x - 2] == 's' && buf[(*x) - 1] == 'p')
	{
		shape->type = 1;
		ret = check_pos(buf, x, &(shape->center), "position of sphere\n");
		shape->dia = read_float(buf, x);
		if (shape->dia < 0)
			return ("Error : diameter must be positive\n");
		ret = join(ret, check_color(buf, x, &(shape->color), "sphere color\n"));
		return (ret);
	}
	shape->type = (buf[*x - 2] == 's') ? 4 : 0;
	ret = check_pos(buf, x, &(shape->center), "vector of plane / square\n");
	ret = check_vec(buf, x, &(shape->vec), "vector of plane / square\n");
	shape->hi = (shape->type == 4) ? read_float(buf, x): 0;
	if (shape->hi < 0)
			return ("Error : height must be positive\n");
	ret = join(ret, check_color(buf, x, &(shape->color), "for plane/square\n"));
	return (ret);
}

char *init_tc(char buf[BUFFER_SIZE], int *x, t_rtx *rtx)
{
	char *ret;
	t_tg *shape;

	if (buf[*x - 2] == 'c' && buf[*x - 1] == 'y')
	{
		return(NULL);
	}
	shape->type = 2;
	ret = check_pos(buf, x, &(shape->vec), "vector of plane / square\n");
	ret = check_vec(buf, x, &(shape->vec), "vector of plane / square\n");
	shape->hi = (shape->type == 4) ? read_float(buf, x) : 0;
	if (shape->hi < 0)
			return ("Error : height must be positive\n");
	ret = join(ret, check_color(buf, x, &(shape->color), "for plane/square\n"));
	return (ret);
}
