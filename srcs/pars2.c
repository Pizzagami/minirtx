/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:07:13 by selgrabl          #+#    #+#             */
/*   Updated: 2019/12/12 18:19:43 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char 		*pars_a(char **buf, t_rtx *rtx)
{
	char	*ret;

	if (!buf[1] || !buf[2])
		return("Missing argument(s) on declaraton of ambiant light");
	if (buf[3] != NULL)
		return("Too many arguments on declaration of ambiant light");
	rtx->amb.ratio = ft_atof(buf[1]);
	if ((isnan(rtx->amb.ratio)))
		return("Invalid number for ratio of ambiant light");
	if (rtx->amb.ratio > 1 || rtx->amb.ratio < 0)
		return ("Value out of range for ratio of ambiant light");
	ret = read_color(buf[2], &(rtx->amb.color), "of ambiant light");
	rtx->amb.color = lfois(rtx->amb.color, rtx->amb.ratio);
	return(ret);
}

char		*pars_r(char **buf, t_rtx *rtx)
{
	if (!buf[1] || !buf[2])
		return("Missing argument(s) on declaraton of resolution");
	if (buf[3] != NULL)
		return("Too many arguments on declaration of resolution");
	rtx->res.x = ft_atoi(buf[1]);
	rtx->res.y = ft_atoi(buf[1]);
	if (rtx->res.x == -42)
		return("Invalid number for x of resolution");
	if (rtx->res.x < 0)
		return("Value out of range for x of resolution");
	if (rtx->res.y == -42)
		return("Invalid number for y of resolution");
	if (rtx->res.y < 0)
		return("Value out of range for y of resolution");
	if (rtx->res.x < rtx->res.y)
		return("X/Y must be supperior to 1");
	return(NULL);
}

char 		*pars_sq(char **buf, t_rtx *rtx)
{
	char *ret;
	t_tg *shape;

	shape = malloc(sizeof(t_tg));
	shape->next = rtx->shape;
	rtx->shape = shape;
	rtx->shape->type = 4;
	if (!buf[1] || !buf[2] || !buf[3] || !buf[4])
		return("Missing argument(s) on declaraton of a square");
	if (buf[5] != NULL)
		return("Too many arguments on declaration of a square");
	ret = read_pos(buf[1], &(rtx->shape->center), " of a square");
	ret = join(ret, read_vec(buf[2], &(rtx->shape->vec), " of a square"));
	rtx->shape->hi = ft_atof(buf[3]);
	if (isnan(rtx->shape->hi))
		return("Invalid number for height of a square");
	if (rtx->shape->hi < 0)
		return("Value out of range for height of a square");
	ret = join(ret, read_color(buf[4], &(rtx->shape->color), " of a square"));
	return(ret);
}

char 		*pars_pl(char **buf, t_rtx *rtx)
{
	char *ret;
	t_tg *shape;

	shape = malloc(sizeof(t_tg));
	shape->next = rtx->shape;
	rtx->shape = shape;
	rtx->shape->type = 0;
	if (!buf[1] || !buf[2] || !buf[3])
		return("Missing argument(s) on declaraton of a plane");
	if (buf[4] != NULL)
		return("Too many arguments on declaration of a plane");
	ret = read_pos(buf[1], &(rtx->shape->center), " of a plane");
	ret = join(ret, read_vec(buf[2], &(rtx->shape->vec), " of a plane"));
	ret = join(ret, read_color(buf[3], &(rtx->shape->color), " of a plane"));
	return(ret);
}

char		*pars_s(char **buf, t_rtx *rtx)
{
	char *ret;
	t_tg *shape;

	shape = malloc(sizeof(t_tg));
	shape->next = rtx->shape;
	rtx->shape = shape;
	rtx->shape->type = 1;
	if (!(buf[1] || buf[2] || buf[3]))
		return("Missing argument(s) on declaraton of a sphere");
	if (buf[4] != NULL)
		return("Too many arguments on declaration of a sphere");
	ret = read_pos(buf[1], &(rtx->shape->center), " of a sphere");
	rtx->shape->dia = ft_atof(buf[2]);
	if (isnan(rtx->shape->dia))
		return("Invalid number for diameter of a sphere");
	if (rtx->shape->dia < 0)
		return("Value out of range for diameter of a sphere");
	ret = join(ret, read_color(buf[3], &(rtx->shape->color), " of a sphere"));
	printf("sphere %f %f\n",shape->center.x, shape->dia);
	return(ret);
}

char		*pars_tr(char **buf, t_rtx *rtx)
{
	char *ret;
	t_tg *shape;

	shape = malloc(sizeof(t_tg));
	shape->next = rtx->shape;
	rtx->shape = shape;
	rtx->shape->type = 3;
	if (!buf[1] || !buf[2] || !buf[3] || !buf[4])
		return("Missing argument(s) on declaraton of triangle");
	if (buf[5] != NULL)
		return("Too many arguments on declaration of triangle");
	ret = read_pos(buf[1], &(rtx->shape->p1), "of triangle");
	ret = join(ret, read_pos(buf[2], &(rtx->shape->p2), "of triangle"));
	ret = join(ret, read_pos(buf[3], &(rtx->shape->p3), "of triangle"));
	ret = join(ret, read_color(buf[4], &(rtx->shape->color), " of triangle"));
	return(ret);}

char		*pars_c(char **buf, t_rtx *rtx)
{
	char *ret;
	t_cam *cam;

	cam = malloc(sizeof(t_cam));
	cam->next = rtx->cam;
	rtx->cam = cam;
	if (!buf[1] || !buf[2] || !buf[3])
		return("Missing argument(s) on declaraton of camera");
	if (buf[4] != NULL)
		return("Too many arguments on declaration of camera");
	ret = read_pos(buf[1], &(rtx->cam->origin), "of camera");
	ret = join(ret, read_vec(buf[2], &(rtx->cam->vec), "of camera"));
	rtx->cam->fov = ft_atoi(buf[3]);
	if (rtx->cam->fov == -42)
		return("Invalid number for FOV of camera");
	if (rtx->cam->fov > 180 || rtx->cam->fov < 0)
		return ("Value out of range for FOV of camera");
	return(ret);
}

char		*pars_l(char **buf, t_rtx *rtx)
{
	char *ret;
	t_light *light;

	light = malloc(sizeof(t_light));
	light->next = rtx->light;
	rtx->light = light;
	if (!buf[1] || !buf[2] || !buf[3])
		return("Missing argument(s) on declaraton of light");
	if (buf[4] != NULL)
		return("Too many arguments on declaration of light");
	ret = read_pos(buf[1], &(rtx->light->pos), "of light");
	rtx->light->ratio = ft_atof(buf[2]);
	if (isnan(rtx->light->ratio))
		return("Invalid number for ratio of light");
	if (rtx->light->ratio > 1 || rtx->light->ratio < 0)
		return ("Value out of range for ratio of light");
	ret = join(ret, read_color(buf[3], &(rtx->light->color), "of light"));
	rtx->light->color = lfois(rtx->light->color, rtx->light->ratio);
	return(ret);
}

char		*pars_cy(char **buf, t_rtx *rtx)
{
	char *ret;
	t_tg *shape;

	shape = malloc(sizeof(t_tg));
	shape->next = rtx->shape;
	rtx->shape = shape;
	rtx->shape->type = 2;
	if (!buf[1] || !buf[2] || !buf[3] || !buf[4] || !buf[5])
		return("Missing argument(s) on declaraton of cylinder");
	if (buf[6] != NULL)
		return("Too many arguments on declaration of cylinder");
	ret = read_pos(buf[1], &(rtx->shape->center), " of cylinder");
	ret = join(ret, read_vec(buf[2], &(rtx->shape->vec), " of cylinder"));
	rtx->shape->dia = ft_atof(buf[3]);
	if (isnan(rtx->shape->dia))
		return("Invalid number for diameter of cylinder");
	rtx->shape->hi = ft_atof(buf[4]);
	if (rtx->shape->dia < 0)
		return("Value out of range for diameter of cylinder");
	if (isnan(rtx->shape->hi))
		return("Invalid number for high of cylinder");
	if (rtx->shape->hi < 0)
		return("Value out of range for high of cylinder");
	ret = join(ret, read_color(buf[5], &(rtx->shape->color), " of cylinder"));
	return(ret);}

char		*pars_ce(char **buf, t_rtx *rtx)
{
	char *ret;
	t_tg *shape;

	shape = malloc(sizeof(t_tg));
	shape->next = rtx->shape;
	rtx->shape = shape;
	rtx->shape->type = 7;
	if (!buf[1] || !buf[2] || !buf[3] || !buf[4])
		return("Missing argument(s) on declaraton of cercle");
	if (buf[5] != NULL)
		return("Too many arguments on declaration of cercle");
	ret = read_pos(buf[1], &(rtx->shape->center), " of cercle");
	ret = join(ret, read_vec(buf[2], &(rtx->shape->vec), " of cercle"));
	rtx->shape->dia = ft_atof(buf[3]);
	if (isnan(rtx->shape->dia))
		return("Invalid number for diameter of cercle");
	if (rtx->shape->hi < 0)
		return("Value out of range for high of cercle");
	ret = join(ret, read_color(buf[4], &(rtx->shape->color), " of cercle"));
	return(ret);
}

char		*pars_py(char **buf, t_rtx *rtx)
{
	buf = buf + 1;
	rtx = rtx + 1;
	return NULL;
}

char		*pars_cu(char **buf, t_rtx *rtx)
{
	buf = buf + 1;
	rtx = rtx + 1;
	return NULL;
}