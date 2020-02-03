/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raimbaultbrieuc <raimbaultbrieuc@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:07:13 by selgrabl          #+#    #+#             */
/*   Updated: 2020/02/03 16:49:30 by raimbaultbr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char		*pars_a(char **buf, t_rtx *rtx)
{
	char	*ret;

	if (!buf[1] || !buf[2])
		return ("Missing argument(s) on declaraton of ambiant light");
	if (buf[3] != NULL)
		return ("Too many arguments on declaration of ambiant light");
	rtx->amb.ratio = ft_atof(buf[1]);
	if ((isnan(rtx->amb.ratio)))
		return ("Invalid number for ratio of ambiant light");
	if (rtx->amb.ratio > 1 || rtx->amb.ratio < 0)
		return ("Value out of range for ratio of ambiant light");
	ret = read_color(buf[2], &(rtx->amb.color), "of ambiant light");
	rtx->amb.color = lfois(rtx->amb.color, rtx->amb.ratio);
	return (ret);
}

char		*pars_r(char **buf, t_rtx *rtx)
{
	if (!buf[1] || !buf[2])
		return ("Missing argument(s) on declaraton of resolution");
	if (buf[3] != NULL)
		return ("Too many arguments on declaration of resolution");
	rtx->res.x = ft_atoi(buf[1]);
	rtx->res.y = ft_atoi(buf[2]);
	if (rtx->res.x == -42)
		return ("Invalid number for x of resolution");
	if (rtx->res.x < 0)
		return ("Value out of range for x of resolution");
	if (rtx->res.y == -42)
		return ("Invalid number for y of resolution");
	if (rtx->res.y < 0)
		return ("Value out of range for y of resolution");
	if (rtx->res.x < rtx->res.y)
		return ("X/Y must be supperior to 1");
	return (NULL);
}

char		*pars_c(char **buf, t_rtx *rtx)
{
	char	*ret;
	t_cam	*cam;

	cam = malloc(sizeof(t_cam));
	cam->next = rtx->cam;
	rtx->cam = cam;
	cam->filter = 0;
	if (!buf[1] || !buf[2] || !buf[3])
		return ("Missing argument(s) on declaraton of camera");
	if (buf[4] != NULL && buf[5] != NULL)
		return ("Too many arguments on declaration of camera");
	ret = read_pos(buf[1], &(rtx->cam->origin), "of camera");
	ret = join(ret, read_vec(buf[2], &(rtx->cam->vec), "of camera"));
	cam->vec = fois(normalize(cam->vec), -1);
	cam->right = normalize(cross(cam->vec, init_vec(0, 1, 0)));
	if (isnan(cam->right.x) && isnan(cam->right.z) && isnan(cam->right.y))
		cam->right = (cam->vec.y > 0) ? init_vec(1, 0, 0) : init_vec(-1, 0, 0);
	cam->up = fois(normalize(cross(cam->right, cam->vec)), -1);
	rtx->cam->fov = ft_atoi(buf[3]);
	if (rtx->cam->fov == -42)
		return ("Invalid number for FOV of camera");
	if (cam->fov > 180 || cam->fov < 0)
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
	cam->rot = init_vec(0, 0, 0);
	return (ret);
}

char		*pars_l(char **buf, t_rtx *rtx)
{
	char	*ret;
	t_light	*light;

	light = malloc(sizeof(t_light));
	light->next = rtx->light;
	rtx->light = light;
	light->para = init_vec(0, 0, 0);
	if (!buf[1] || !buf[2] || !buf[3])
		return ("Missing argument(s) on declaraton of light");
	if (buf[4] != NULL && buf[5] != NULL)
		return ("Too many arguments on declaration of light");
	ret = read_pos(buf[1], &(light->pos), "of light");
	light->ratio = ft_atof(buf[2]);
	if (isnan(light->ratio))
		return ("Invalid number for ratio of light");
	if (light->ratio > 1 || light->ratio < 0)
		return ("Value out of range for ratio of light");
	ret = join(ret, read_color(buf[3], &(rtx->light->color), "of light"));
	rtx->light->color = lfois(rtx->light->color, rtx->light->ratio);
	if (buf[4])
		ret = read_vec(buf[4], &(light->para), "vector of parallel light");
	return (ret);
}

char		*pars_pl(char **buf, t_rtx *rtx)
{
	char *ret;
	t_tg *shape;

	shape = malloc(sizeof(t_tg));
	shape->next = rtx->shape;
	rtx->shape = shape;
	shape->type = 0;
	shape->trans = 0;
	shape->refl = 0;
	shape->dam = 0;
	if (!buf[1] || !buf[2] || !buf[3])
		return ("Missing argument(s) on declaraton of a plane");
	if (buf[4] != NULL && buf[5] != NULL && buf[6] != NULL && buf[7] != NULL)
		return ("Too many arguments on declaration of a plane");
	ret = read_pos(buf[1], &(shape->center), " of a plane");
	ret = join(ret, read_vec(buf[2], &(shape->normal), " of a plane"));
	ret = join(ret, read_color(buf[3], &(shape->color), " of a plane"));
	if (buf[4])
		ret = join(ret, read_float(buf[4], &(rtx->shape->trans), "transparence of a plane", 1));
	if (buf[4] && buf[5])
		ret = join(ret, read_float(buf[5], &(rtx->shape->refl), "reflection of a plane", 1));
	return (ret);
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
	shape->dam = 0;
	if (!(buf[1] || buf[2] || buf[3]))
		return ("Missing argument(s) on declaraton of a sphere");
	if (buf[4] != NULL && buf[5] != NULL && buf[6] != NULL && buf[7] != NULL)
		return ("Too many arguments on declaration of a sphere");
	ret = read_pos(buf[1], &(rtx->shape->center), " of a sphere");
	ret = join(ret, read_float(buf[2], &(shape->dia), " diameter of a sphere", -1));
	ret = join(ret, read_color(buf[3], &(shape->color), " of a sphere"));
	if (buf[4])
		ret = join(ret, read_float(buf[4], &(shape->trans), " transparence of a sphere", 1));
	if (buf[4] && buf[5])
		ret = join(ret, read_float(buf[5], &(shape->refl), " reflection of a sphere", 1));
	if (buf[4] && buf[5] && buf[6])
		ret = join(ret, read_float(buf[6], &(shape->dam), "damier", -1));
	return (ret);
}

char		*pars_sm(char **buf, t_rtx *rtx)
{
	char	*ret;
	t_tg	*shape;
	void	*map_ptr;
	int		x;

	shape = malloc(sizeof(t_tg));
	shape->next = rtx->shape;
	rtx->shape = shape;
	shape->type = 11;
	shape->trans = 0;
	shape->refl = 0;
	shape->v1 = init_vec(0, -1, 0);
	shape->v2 = init_vec(-1, 0, 0);
	if (!(buf[1] || buf[2] || buf[3]))
		return ("Missing argument(s) on declaraton of a mapped sphere");
	if (buf[4] != NULL)
		return ("Too many arguments on declaration of a mapped sphere");
	ret = read_pos(buf[1], &(rtx->shape->center), " of a mapped sphere");
	ret = join(ret, read_float(buf[2], &(shape->dia), " diameter of a mapped sphere", -1));
	map_ptr = mlx_xpm_file_to_image(rtx->mlx_ptr, buf[3], &(shape->map_res.x), &(shape->map_res.y));
	shape->map_id = mlx_get_data_addr(map_ptr, &x, &x, &x);
	return (ret);
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
	shape->dam = 0;
	if (!buf[1] || !buf[2] || !buf[3] || !buf[4])
		return ("Missing argument(s) on declaraton of triangle");
	if (buf[5] != NULL && buf[6] != NULL && buf[7] != NULL)
		return ("Too many arguments on declaration of triangle");
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
	return (ret);
}

char		*pars_cy(char **buf, t_rtx *rtx)
{
	char	*ret;
	t_tg	*shape;
	float	x;

	shape = malloc(sizeof(t_tg));
	shape->next = rtx->shape;
	rtx->shape = shape;
	shape->type = 2;
	shape->trans = 0;
	shape->refl = 0;
	shape->dam = 0;
	x = 0;
	if (!buf[1] || !buf[2] || !buf[3] || !buf[4] || !buf[5])
		return ("Missing argument(s) on declaraton of cylinder");
	if (buf[6] != NULL && buf[7] != NULL && buf[8] != NULL && buf[9] != NULL)
		return ("Too many arguments on declaration of cylinder");
	ret = read_pos(buf[1], &(shape->center), " of cylinder");
	ret = join(ret, read_vec(buf[2], &(shape->vec), " of cylinder"));
	shape->dia = ft_atof(buf[3]);
	if (isnan(rtx->shape->dia))
		return ("Invalid number for diameter of cylinder");
	shape->hi = ft_atof(buf[4]);
	if (shape->dia < 0)
		return ("Value out of range for diameter of cylinder");
	if (isnan(shape->hi))
		return ("Invalid number for high of cylinder");
	if (shape->hi < 0)
		return ("Value out of range for high of cylinder");
	ret = join(ret, read_color(buf[5], &(shape->color), " of cylinder"));
	if (buf[6])
		ret = join(ret, read_float(buf[6], &(shape->trans), " transparence of a cylinder", 1));
	if (buf[6] && buf[7])
		ret = join(ret, read_float(buf[7], &(shape->refl), " reflection of a cylinder", 1));
	if (buf[6] && buf[7] && buf[8])
		ret = join(ret, read_float(buf[8], &x, "capuchon of a cylinder", -1));
	shape->vec = normalize(shape->vec);
	if (x == 1)
		creat_ce(*shape, rtx);
	return (ret);
}

char		*pars_co(char **buf, t_rtx *rtx)
{
	char *ret;
	t_tg *shape;

	shape = malloc(sizeof(t_tg));
	shape->next = rtx->shape;
	rtx->shape = shape;
	shape->type = 32;
	shape->trans = 0;
	shape->refl = 0;
	shape->dam = 0;
	if (!buf[1] || !buf[2] || !buf[3] || !buf[4] || !buf[5])
		return ("Missing argument(s) on declaraton of cone");
	if (buf[6] != NULL)
		return ("Too many arguments on declaration of cone");
	ret = read_pos(buf[1], &(shape->center), " of cone");
	ret = join(ret, read_vec(buf[2], &(shape->vec), " of cone"));
	shape->dia = ft_atof(buf[3]);
	if (isnan(rtx->shape->dia))
		return ("Invalid number for diameter of cone");
	shape->hi = ft_atof(buf[4]);
	if (shape->dia < 0 || shape->dia > 90)
		return ("Value out of range for angle of cone");
	if (isnan(shape->hi))
		return ("Invalid number for high of cone");
	if (shape->hi < 0)
		return ("Value out of range for high of cone");
	ret = join(ret, read_color(buf[5], &(shape->color), " of cone"));
	shape->vec = normalize(shape->vec);
	shape->dia *= M_PI / 180;
	return (ret);
}

char		*pars_sa(char **buf, t_rtx *rtx)
{
	char *ret;
	t_tg *shape;

	shape = malloc(sizeof(t_tg));
	shape->next = rtx->shape;
	rtx->shape = shape;
	shape->type = 21;
	shape->trans = 0;
	shape->refl = 0;
	shape->dam = 0;
	if (!buf[1] || !buf[2] || !buf[3] || !buf[4] || !buf[5])
		return ("Missing argument(s) on declaraton of sablier");
	if (buf[6] != NULL)
		return ("Too many arguments on declaration of sablier");
	ret = read_pos(buf[1], &(shape->center), " of sablier");
	ret = join(ret, read_vec(buf[2], &(shape->vec), " of sablier"));
	shape->dia = ft_atof(buf[3]);
	if (isnan(rtx->shape->dia))
		return ("Invalid number for diameter of sablier");
	shape->hi = ft_atof(buf[4]);
	if (shape->dia < 0 || shape->dia > 90)
		return ("Value out of range for angle of sablier");
	if (isnan(shape->hi))
		return ("Invalid number for high of sablier");
	if (shape->hi < 0)
		return ("Value out of range for high of sablier");
	ret = join(ret, read_color(buf[5], &(shape->color), " of sablier"));
	shape->vec = normalize(shape->vec);
	shape->dia *= M_PI / 180;
	return (ret);
}

char		*pars_ce(char **buf, t_rtx *rtx)
{
	char *ret;
	t_tg *shape;

	shape = malloc(sizeof(t_tg));
	shape->next = rtx->shape;
	rtx->shape = shape;
	shape->type = 7;
	shape->trans = 0;
	shape->refl = 0;
	if (!buf[1] || !buf[2] || !buf[3] || !buf[4])
		return ("Missing argument(s) on declaraton of cercle");
	if (buf[5] != NULL)
		return ("Too many arguments on declaration of cercle");
	ret = read_pos(buf[1], &(shape->center), " of cercle");
	ret = join(ret, read_vec(buf[2], &(shape->normal), " of cercle"));
	shape->dia = ft_atof(buf[3]);
	if (isnan(shape->dia))
		return ("Invalid number for diameter of cercle");
	if (shape->dia < 0)
		return ("Value out of range for diameter of cercle");
	ret = join(ret, read_color(buf[4], &(shape->color), " of cercle"));
	return (ret);
}

char		*pars_t(char **buf, t_rtx *rtx)
{
	char *ret;
	t_tg *shape;

	shape = malloc(sizeof(t_tg));
	shape->next = rtx->shape;
	rtx->shape = shape;
	shape->type = 42;
	shape->trans = 0;
	shape->refl = 0;
	if (!buf[1] || !buf[2] || !buf[3] || !buf[4] || !buf[5])
		return ("Missing argument(s) on declaraton of torus");
	if (buf[6] != NULL)
		return ("Too many arguments on declaration of torus");
	ret = read_pos(buf[1], &(shape->center), " of torus");
	ret = join(ret, read_vec(buf[2], &(shape->normal), " of torus"));
	shape->dia = ft_atof(buf[3]);
	shape->hi = ft_atof(buf[4]);
	if (isnan(shape->dia))
		return ("Invalid number for diameter of torus");
	if (isnan(shape->hi))
		return ("Invalid number for diameter of torus");
	if (shape->dia < 0)
		return ("Value out of range for diameter of torus");
	ret = join(ret, read_color(buf[5], &(shape->color), " of torus"));
	return (ret);
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
	shape->dam = 0;
	if (!buf[1] || !buf[2] || !buf[3] || !buf[4] || !buf[5])
		return ("Missing argument(s) on declaraton of a pyramide");
	if (buf[6] != NULL && buf[7] != NULL && buf[8] != NULL)
		return ("Too many arguments on declaration of a pyramide");
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
	return (ret);
}

char		*pars_sq(char **buf, t_rtx *rtx)
{
	char *ret;
	t_tg *shape;

	shape = malloc(sizeof(t_tg));
	shape->next = rtx->shape;
	rtx->shape = shape;
	shape->type = 4;
	shape->trans = 0;
	shape->refl = 0;
	shape->dam = 0;
	if (!buf[1] || !buf[2] || !buf[3] || !buf[4])
		return ("Missing argument(s) on declaraton of a square");
	if (buf[5] != NULL && buf[6] != NULL && buf[7] != NULL)
		return ("Too many arguments on declaration of a square");
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
	return (ret);
}

char		*pars_cu(char **buf, t_rtx *rtx)
{
	char	*ret;
	t_rtx	inf;

	if (!buf[1] || !buf[2] || !buf[3] || !buf[4])
		return ("Missing argument(s) on declaraton of a cube");
	if (buf[5] != NULL && buf[6] != NULL && buf[7] != NULL)
		return ("Too many arguments on declaration of a cube");
	ret = pars_sq(buf, &inf);
	if (ret)
		return (ret);
	pars_sqr(1, *(inf.shape), rtx);
	pars_sqr(-1, *(inf.shape), rtx);
	pars_sqr(2, *(inf.shape), rtx);
	pars_sqr(-2, *(inf.shape), rtx);
	pars_sqr(3, *(inf.shape), rtx);
	pars_sqr(-3, *(inf.shape), rtx);
	return (ret);
}

char		*pars_aa(char **buf, t_rtx *rtx)
{
	(void)buf;
	rtx->aa = 2;
	return (NULL);
}

void		pars_sqr(int x, t_tg info, t_rtx *rtx)
{
	t_tg *shape;

	shape = malloc(sizeof(t_tg));
	shape->next = rtx->shape;
	rtx->shape = shape;
	shape->type = 4;
	shape->dam = 0;
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
	shape->center = (x > 0) ? plus(info.center, fois(shape->vec, info.hi / 2)) :
	plus(info.center, fois(shape->vec, -info.hi / 2));
	corners(shape);
	tri_vecs(shape);
	shape->vec = normalize(cross(min(shape->p2, shape->p1),
		min(shape->p3, shape->p1)));
	shape->normal = shape->vec;
}

void		creat_ce(t_tg shape, t_rtx *rtx)
{
	t_tg *shape1;
	t_tg *shape2;

	shape1 = malloc(sizeof(t_tg));
	shape1->next = rtx->shape;
	shape1->type = 7;
	shape1->color = shape.color;
	shape1->dia = shape.dia / 2;
	shape1->normal = shape.vec;
	shape1->refl = shape.refl;
	shape1->trans = shape.trans;
	shape1->center = plus(shape.center, fois(shape.vec, shape.hi / 2));
	shape2 = malloc(sizeof(t_tg));
	*shape2 = *shape1;
	shape2->next = shape1;
	rtx->shape = shape2;
	shape2->center = min(shape.center, fois(shape.vec, shape.hi / 2));
}
