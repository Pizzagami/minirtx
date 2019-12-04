/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:07:13 by selgrabl          #+#    #+#             */
/*   Updated: 2019/12/04 12:52:02 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char *init_ar(char buf[BUFFER_SIZE], int *x, t_rtx *rtx)
{
	(*x)++;
	if (buf[(*x) - 1] == 'A')
	{
		if (rtx->amb.color.b != -1)
			return ("Error : Only one ambiant light allowed\n");
		rtx->amb.ratio = read_float(buf, x);
		if (rtx->amb.ratio == NAF)
			return("Error : Invalid float for ratio of ambiant light\n");
		if (rtx->amb.ratio > 1 || rtx->amb.ratio < 0)
			return("Error : Value out of range for ratio of ambiant light\n");
		return(read_color(buf, x, &(rtx->amb.color), "ambiante light\n"));
	}
	if (rtx->amb.color.b != -1)
		return ("Error : Only one resolution allowed\n");
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
	char	*ret;
	t_cam	*cam;
	t_light	*light;
	
	(*x) += 2;
	if (buf[*x - 2] == 'c' && buf[*x - 1] == ' ')
	{
		cam = malloc(sizeof(t_cam));
		cam->next = rtx->cam;
		rtx->cam = cam;
		ret = read_pos(buf, x, &(cam->origin), "position of camera\n");
		ret = join(ret, read_vec(buf, x, &(cam->vec), "vector of camera\n"));
		cam->fov = read_int(buf, x);
		return((cam->fov < 0 || cam->fov > 180 || cam->fov == NAF) ?
		("Error : Invalid float for field of view\n") : (ret));
	}
		light = malloc(sizeof(t_light));
		light->next = rtx->light;
		rtx->light = light;
		ret = read_pos(buf, x, &(light->pos), "origin of light\n");
		light->ratio = read_float(buf, x);
		if (light->ratio == NAF)
			return("Error : Invalid float for ratio a light\n");
		if (light->ratio > 1 || light->ratio < 0)
			return("Error : Value out of range for ratio of a light\n");
		return(join(ret, read_color(buf, x, &(light->color), "light color\n")));
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
		ret = read_pos(buf, x, &(shape->center), "position of sphere\n");
		shape->dia = read_float(buf, x);
		if (shape->dia < 0)
			return ("Error : diameter must be positive\n");
		ret = join(ret, read_color(buf, x, &(shape->color), "sphere color\n"));
		return (ret);
	}
	shape->type = (buf[*x - 2] == 's') ? 4 : 0;
	ret = read_pos(buf, x, &(shape->center), "vector of plane / square\n");
	ret = join(ret, read_vec(buf, x, &(shape->vec), "vector of plane/square\n"));
	shape->hi = (shape->type == 4) ? read_float(buf, x): 0;
	if (shape->hi < 0)
			return ("Error : height must be positive\n");
	ret = join(ret, read_color(buf, x, &(shape->color), "for plane/square\n"));
	return (ret);
}

char *init_tc(char buf[BUFFER_SIZE], int *x, t_rtx *rtx)
{
	char *ret;
	t_tg *shape;

	shape = malloc(sizeof(t_tg));
	shape->next = rtx->shape;
	rtx->shape = shape;
	(*x) += 2;
	if (buf[*x - 2] == 'c' && buf[*x - 1] == 'y')
	{
		shape->type = 2;
		ret = read_pos(buf, x, &(shape->center), "position of cylindre\n");
		ret = join(ret, read_vec(buf, x, &(shape->vec), "vector of cylindre\n"));
		shape->dia = read_float(buf, x);
		if (shape->dia < 0)
			ret = join(ret,"Error : diameter must be positive\n");
		shape->hi = read_float(buf, x);
		if (shape->hi < 0)
			ret = join(ret,"Error : height of cylinder must be positive\n");
		ret = join(ret, read_color(buf, x, &(shape->color), "cylindre color\n"));
		return(ret);
	}
	shape->type = 3;
	ret = read_pos(buf, x, &(shape->p1), "1st point of triangle\n");
	ret = join(ret, read_pos(buf, x, &(shape->p2), "2nd point of triangle\n"));
	ret = join(ret, read_pos(buf, x, &(shape->p3), "3rd point of triangle\n"));
	ret = join(ret, read_color(buf, x, &(shape->color), "color of triangle\n"));
	return(ret);
}
