/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:07:13 by selgrabl          #+#    #+#             */
/*   Updated: 2020/01/05 18:40:29 by selgrabl         ###   ########.fr       */
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
	shape->vec = normalize(shape->vec);
	find_vecs(shape);
	corners(shape);
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
	shape->vec = normalize(cross(min(shape->p2, shape->p1),
		min(shape->p3, shape->p1)));
	shape->center = shape->p1;
	return(ret);
}

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
	shape->type = 2;
	if (!buf[1] || !buf[2] || !buf[3] || !buf[4] || !buf[5])
		return("Missing argument(s) on declaraton of cylinder");
	if (buf[6] != NULL)
		return("Too many arguments on declaration of cylinder");
	ret = read_pos(buf[1], &(shape->center), " of cylinder");
	ret = join(ret, read_vec(buf[2], &(shape->vec), " of cylinder"));
	rtx->shape->dia = ft_atof(buf[3]);
	if (isnan(rtx->shape->dia))
		return("Invalid number for diameter of cylinder");
	shape->hi = ft_atof(buf[4]);
	if (shape->dia < 0)
		return("Value out of range for diameter of cylinder");
	if (isnan(shape->hi))
		return("Invalid number for high of cylinder");
	if (rtx->shape->hi < 0)
		return("Value out of range for high of cylinder");
	ret = join(ret, read_color(buf[5], &(shape->color), " of cylinder"));
	return(ret);
}

char		*pars_ce(char **buf, t_rtx *rtx)
{
	char *ret;
	t_tg *shape;

	shape = malloc(sizeof(t_tg));
	shape->next = rtx->shape;
	rtx->shape = shape;
	shape->type = 7;
	if (!buf[1] || !buf[2] || !buf[3] || !buf[4])
		return("Missing argument(s) on declaraton of cercle");
	if (buf[5] != NULL)
		return("Too many arguments on declaration of cercle");
	ret = read_pos(buf[1], &(rtx->shape->center), " of cercle");
	ret = join(ret, read_vec(buf[2], &(shape->vec), " of cercle"));
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
	t_tg *shape;
	t_vec	v1;
	t_vec	v2;
	t_vec	n;
	float	hi;
	float	si;

	shape = malloc(sizeof(t_tg));
	shape->next = rtx->shape;
	rtx->shape = shape;
	rtx->shape->type = 3;
	read_pos(buf[1], &(shape->center), "test");
	read_vec(buf[2], &n, "test");
	si = atof(buf[3]);
	hi = atof(buf[4]);
	read_color(buf[5], &(shape->color), "test");
	v1.x = n.y;
	v1.y = n.z;
	v1.z = n.x;
	v2 = cross(n, v1);
	shape->p1 = plus(shape->center, fois(n, hi));
	shape->p2 = min(min(shape->center, fois(v1, si / 2)), fois(v2, si / 2));
	shape->p3 = min(plus(shape->center, fois(v1, si / 2)), fois(v2, si / 2));
	shape = malloc(sizeof(t_tg));
	shape->center = rtx->shape->center;
	shape->color = rtx->shape->color;
	shape->p1 = plus(shape->center, fois(n, hi));
	shape->p2 = min(plus(shape->center, fois(v1, si / 2)), fois(v2, si / 2));
	shape->p3 = plus(plus(shape->center, fois(v1, si / 2)), fois(v2, si / 2));
	shape->next = rtx->shape;
	rtx->shape = shape;
	rtx->shape->type = 3;
	shape = malloc(sizeof(t_tg));
	shape->center = rtx->shape->center;
	shape->color = rtx->shape->color;
	shape->p1 = plus(shape->center, fois(n, hi));
	shape->p2 = plus(min(shape->center, fois(v1, si / 2)), fois(v2, si / 2));
	shape->p3 = plus(plus(shape->center, fois(v1, si / 2)), fois(v2, si / 2));
	shape->next = rtx->shape;
	rtx->shape = shape;
	rtx->shape->type = 3;
	shape = malloc(sizeof(t_tg));
	shape->center = rtx->shape->center;
	shape->color = rtx->shape->color;
	shape->p1 = plus(shape->center, fois(n, hi));
	shape->p2 = plus(min(shape->center, fois(v1, si / 2)), fois(v2, si / 2));
	shape->p3 = min(min(shape->center, fois(v1, si / 2)), fois(v2, si / 2));
	shape->next = rtx->shape;
	rtx->shape = shape;
	rtx->shape->type = 3;
	return(NULL);
}

char		*pars_cu(char **buf, t_rtx *rtx)
{
	char *ret;
	t_rtx inf;

	if (!buf[1] || !buf[2] || !buf[3] || !buf[4])
		return("Missing argument(s) on declaraton of a cube");
	if (buf[5] != NULL)
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
	print_vecs(2,shape->vec,shape->center);
	shape->vec = normalize(cross(min(shape->p2, shape->p1),
		min(shape->p3, shape->p1)));
	//printf("%d %f %f %f %f \n\n",x,sqrt(dot(shape->p1,shape->p2)),sqrt(dot(shape->p3,shape->p4)),sqrt(dot(shape->p3,shape->p2)),sqrt(dot(shape->p1,shape->p4)));
	printf("\n*%f*\n",sqrt(pow(3.53553- (-3.535534), 2) + pow(0 - (0),2) + pow(-53.535534 - (-46.464466), 2)));
}