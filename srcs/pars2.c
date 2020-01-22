/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:07:13 by selgrabl          #+#    #+#             */
/*   Updated: 2020/01/22 10:48:03 by braimbau         ###   ########.fr       */
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
	rtx->res.y = ft_atoi(buf[2]);
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

char		*pars_c(char **buf, t_rtx *rtx)
{
	char *ret;
	t_cam *cam;

	cam = malloc(sizeof(t_cam));
	cam->next = rtx->cam;
	rtx->cam = cam;
	cam->filter = 0;
	if (!buf[1] || !buf[2] || !buf[3])
		return("Missing argument(s) on declaraton of camera");
	if (buf[4] != NULL && buf[5] != NULL)
		return("Too many arguments on declaration of camera");
	ret = read_pos(buf[1], &(rtx->cam->origin), "of camera");
	ret = join(ret, read_vec(buf[2], &(rtx->cam->vec), "of camera"));
	rtx->cam->fov = ft_atoi(buf[3]);
	if (rtx->cam->fov == -42)
		return("Invalid number for FOV of camera");
	if (rtx->cam->fov > 180 || rtx->cam->fov < 0)
		return ("Value out of range for FOV of camera");
	if (buf[4])
	{
		if (buf[4][0] == '3' && buf[4][1] == 'D' && buf[4][2] == 0)
		{
			cam->origin.x -= 2;
			cam->filter = 'l';
			buf[4][0] = 'r';
			buf[4][1] = 0;
			pars_c(buf, rtx);
		}
		else if ((buf[4][0] == 'R' || buf[4][0] == 'G' || buf[4][0] == 'B' || buf[4][0] == 'C' ||
		buf[4][0] == 'Y' || buf[4][0] == 'P' || buf[4][0] == 'W' || buf[4][0] == 'N' ||
		buf[4][0] == 'S' || buf[4][0] == 'r') && buf[4][1] == 0)
		{
				cam->filter = buf[4][0];
		}
		else
			return ("Invalid value for filter of camera");
	}
	cam->rot = init_vec(0,0,0);
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

char 		*pars_pl(char **buf, t_rtx *rtx)
{
	char *ret;
	t_tg *shape;

	shape = malloc(sizeof(t_tg));
	shape->next = rtx->shape;
	rtx->shape = shape;
	rtx->shape->type = 0;
	rtx->shape->trans = 0;
	rtx->shape->refl = 0;
	if (!buf[1] || !buf[2] || !buf[3])
		return("Missing argument(s) on declaraton of a plane");
	if (buf[4] != NULL && buf[5] != NULL && buf[6] != NULL)
		return("Too many arguments on declaration of a plane");
	ret = read_pos(buf[1], &(rtx->shape->center), " of a plane");
	ret = join(ret, read_vec(buf[2], &(rtx->shape->normal), " of a plane"));
	ret = join(ret, read_color(buf[3], &(rtx->shape->color), " of a plane"));
	if (buf[4])
		ret = join(ret, read_float(buf[4], &(rtx->shape->trans), "transparence of a plane", 1));
	if (buf[4] && buf[5])
		ret = join(ret, read_float(buf[5], &(rtx->shape->refl), "reflection of a plane", 1));	
	return(ret);
}

char		*pars_s(char **buf, t_rtx *rtx)
{
	char *ret;
	t_tg *shape;

	shape = malloc(sizeof(t_tg));
	shape->next = rtx->shape;
	rtx->shape = shape;
	shape->type = 1;
	shape->trans = 0;
	shape->refl = 0;
	if (!(buf[1] || buf[2] || buf[3]))
		return("Missing argument(s) on declaraton of a sphere");
	if (buf[4] != NULL && buf[5] != NULL && buf[6] != NULL)
		return("Too many arguments on declaration of a sphere");
	ret = read_pos(buf[1], &(rtx->shape->center), " of a sphere");
	ret = join(ret, read_float(buf[2], &(shape->dia), " diameter of a sphere", -1));
	ret = join(ret, read_color(buf[3], &(shape->color), " of a sphere"));
	if (buf[4])
		ret = join(ret, read_float(buf[4], &(shape->trans), " transparence of a sphere", 1));
	if (buf[4] && buf[5])
	ret = join(ret, read_float(buf[5], &(shape->refl), " reflection of a sphere", 1));
	return(ret);
}

char		*pars_tr(char **buf, t_rtx *rtx)
{
	char *ret;
	t_tg *shape;

	shape = malloc(sizeof(t_tg));
	shape->next = rtx->shape;
	rtx->shape = shape;
	shape->type = 3;
	shape->trans = 0;
	shape->refl = 0;
	if (!buf[1] || !buf[2] || !buf[3] || !buf[4])
		return("Missing argument(s) on declaraton of triangle");
	if (buf[5] != NULL && buf[6] != NULL && buf[7] != NULL)
		return("Too many arguments on declaration of triangle");
	ret = read_pos(buf[1], &(shape->p1), "of triangle");
	ret = join(ret, read_pos(buf[2], &(shape->p2), "of triangle"));
	ret = join(ret, read_pos(buf[3], &(shape->p3), "of triangle"));
	ret = join(ret, read_color(buf[4], &(shape->color), " of triangle"));
	shape->normal = normalize(cross(min(shape->p2, shape->p1),
		min(shape->p3, shape->p1)));
	shape->center = shape->p1;
	if (buf[5])
		ret = join(ret, read_float(buf[5], &(shape->trans), " transparence of a triangle", 1));
	if (buf[5] && buf[6])
	ret = join(ret, read_float(buf[6], &(shape->refl), " reflection of a triangle", 1));
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
	rtx->shape->trans = 0;
	rtx->shape->refl = 0;
	if (!buf[1] || !buf[2] || !buf[3] || !buf[4] || !buf[5])
		return("Missing argument(s) on declaraton of cylinder");
	if (buf[6] != NULL)
		return("Too many arguments on declaration of cylinder");
	ret = read_pos(buf[1], &(shape->center), " of cylinder");
	ret = join(ret, read_vec(buf[2], &(shape->vec), " of cylinder"));
	shape->dia = ft_atof(buf[3]);
	if (isnan(rtx->shape->dia))
		return("Invalid number for diameter of cylinder");
	shape->hi = ft_atof(buf[4]);
	if (shape->dia < 0)
		return("Value out of range for diameter of cylinder");
	if (isnan(shape->hi))
		return("Invalid number for high of cylinder");
	if (shape->hi < 0)
		return("Value out of range for high of cylinder");
	ret = join(ret, read_color(buf[5], &(shape->color), " of cylinder"));
	shape->vec = normalize(shape->vec);
	return(ret);
}

char		*pars_ce(char **buf, t_rtx *rtx)
{
	char *ret;
	t_tg *shape;

	shape = malloc(sizeof(t_tg));
	shape->next = rtx->shape;
	rtx->shape = shape;
	rtx->shape->type = 7;
	rtx->shape->trans = 0;
	rtx->shape->refl = 0;
	if (!buf[1] || !buf[2] || !buf[3] || !buf[4])
		return("Missing argument(s) on declaraton of cercle");
	if (buf[5] != NULL)
		return("Too many arguments on declaration of cercle");
	ret = read_pos(buf[1], &(rtx->shape->center), " of cercle");
	ret = join(ret, read_vec(buf[2], &(shape->normal), " of cercle"));
	shape->dia = ft_atof(buf[3]);
	if (isnan(shape->dia))
		return("Invalid number for diameter of cercle");
	if (shape->dia < 0)
		return("Value out of range for diameter of cercle");
	ret = join(ret, read_color(buf[4], &(shape->color), " of cercle"));
	return(ret);
}

char		*pars_py(char **buf, t_rtx *rtx)
{
	char *ret;
	t_tg *shape;

	shape = malloc(sizeof(t_tg));
	shape->next = rtx->shape;
	rtx->shape = shape;
	shape->type = 4;
	shape->trans = 0;
	shape->refl = 0;
	if (!buf[1] || !buf[2] || !buf[3] || !buf[4] || !buf[5])
		return("Missing argument(s) on declaraton of a pyramide");
	if (buf[6] != NULL && buf[7] != NULL && buf[8] != NULL)
		return("Too many arguments on declaration of a pyramide");
	ret = read_pos(buf[1], &(shape->center), " of a pyramide");
	ret = join(ret, read_vec(buf[2], &(shape->vec), " of a pyramide"));
	ret = join(ret, read_float(buf[3], &(shape->hi), "height of a pyramide", -1));
	ret = join(ret, read_float(buf[4], &(shape->dia), "side of a pyramide", -1));
	ret = join(ret, read_color(buf[5], &(shape->color), " of a pyramide"));
	if (buf[6])
		ret = join(ret, read_float(buf[6], &(shape->trans), "transparence of a pyramide", 1));
	if (buf[6] && buf[7])
		ret = join(ret, read_float(buf[7], &(shape->refl), "reflection of a pyramide", 1));
	shape->vec = normalize(shape->vec);
	find_vecs(shape);
	corners(shape);
	shape->vec = normalize(cross(min(shape->p2, shape->p1),
		min(shape->p3, shape->p1)));
	create_tri(plus(shape->center, fois(shape->vec, shape->dia)), shape->p1, shape->p2, rtx);
	create_tri(plus(shape->center, fois(shape->vec, shape->dia)), shape->p2, shape->p3, rtx);
	create_tri(plus(shape->center, fois(shape->vec, shape->dia)), shape->p3, shape->p4, rtx);
	create_tri(plus(shape->center, fois(shape->vec, shape->dia)), shape->p4, shape->p1, rtx);
	shape->normal = shape->vec;
	return(ret);
}

char 		*pars_sq(char **buf, t_rtx *rtx)
{
	char *ret;
	t_tg *shape;

	shape = malloc(sizeof(t_tg));
	shape->next = rtx->shape;
	rtx->shape = shape;
	shape->type = 4;
	shape->trans = 0;
	shape->refl = 0;
	if (!buf[1] || !buf[2] || !buf[3] || !buf[4])
		return("Missing argument(s) on declaraton of a square");
	if (buf[5] != NULL && buf[6] != NULL && buf[7] != NULL)
		return("Too many arguments on declaration of a square");
	ret = read_pos(buf[1], &(shape->center), " of a square");
	ret = join(ret, read_vec(buf[2], &(shape->vec), " of a square"));
	ret = join(ret, read_float(buf[3], &(shape->hi), "height of a square", -1));
	ret = join(ret, read_color(buf[4], &(shape->color), " of a square"));
	if (buf[5])
		ret = join(ret, read_float(buf[5], &(shape->trans), "transparence of a square", 1));
	if (buf[5] && buf[6])
		ret = join(ret, read_float(buf[6], &(shape->refl), "reflection of a square", 1));
	shape->vec = normalize(shape->vec);
	find_vecs(shape);
	corners(shape);
	shape->vec = normalize(cross(min(shape->p2, shape->p1),
		min(shape->p3, shape->p1)));
	shape->normal = shape->vec;
	return(ret);
}

char		*pars_cu(char **buf, t_rtx *rtx)
{
	char *ret;
	t_rtx inf;
	if (!buf[1] || !buf[2] || !buf[3] || !buf[4])
		return("Missing argument(s) on declaraton of a cube");
	if (buf[5] != NULL && buf[6] != NULL && buf[7] != NULL)
		return("Too many arguments on declaration of a cube");
	ret = pars_sq(buf, &inf);
	if(ret)
		return(ret);
	pars_sqr(1, *(inf.shape), rtx);
	pars_sqr(-1, *(inf.shape), rtx);
	pars_sqr(2, *(inf.shape), rtx);
	pars_sqr(-2, *(inf.shape), rtx);
	pars_sqr(3, *(inf.shape), rtx);
	pars_sqr(-3, *(inf.shape), rtx);

	return(ret);
}

void		pars_sqr(int x, t_tg info, t_rtx *rtx)
{
	t_tg *shape;
	shape = malloc(sizeof(t_tg));
	shape->next = rtx->shape;
	rtx->shape = shape;
	shape->type = 4;
	shape->hi = info.hi;
	shape->color = info.color;
	shape->vec = info.vec;
	shape->v1 = info.v1;
	shape->v2 = info.v2;
	shape->trans = info.trans;
	shape->refl = info.refl;
	if (abs(x) == 2)
	{
		shape->vec = info.v1;
		shape->v1 = info.vec;
		shape->v2 = info.v2;
	}
	if (abs(x) == 3)
	{
		shape->vec = info.v2;
		shape->v1 = info.vec;
		shape->v2 = info.v1;
	}
	shape->center = (x > 0)? plus(info.center, fois(shape->vec, info.hi / 2)):
	plus(info.center, fois(shape->vec, -info.hi / 2));
	corners(shape);
	tri_vecs(shape);
	shape->vec = normalize(cross(min(shape->p2, shape->p1),
		min(shape->p3, shape->p1)));
	shape->normal = shape->vec;
}
