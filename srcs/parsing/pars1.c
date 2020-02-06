/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:30:24 by selgrabl          #+#    #+#             */
/*   Updated: 2020/02/06 15:58:04 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

char		*pars_pl(char **buf, t_rtx *rtx)
{
	char *ret;
	t_tg *shape;

	shape = malloc(sizeof(t_tg));
	shape->next = rtx->shape;
	rtx->shape = shape;
	shape->type = 0;
	init_trd(shape);
	if (!buf[1] || !buf[2] || !buf[3])
		return ("Missing argument(s) on declaraton of a plane");
	if (buf[4] != NULL && buf[5] != NULL && buf[6] != NULL && buf[7] != NULL)
		return ("Too many arguments on declaration of a plane");
	ret = read_pos(buf[1], &(shape->center), " of a plane");
	ret = join(ret, read_vec(buf[2], &(shape->normal), " of a plane"));
	ret = join(ret, read_color(buf[3], &(shape->color), " of a plane"));
	ret = (buf[4]) ? join(ret, read_float(buf[4], &(rtx->shape->trans),
		"transparence of a plane", 1)) : 0;
	ret = (buf[4] && buf[5]) ? join(ret, read_float(buf[5], &(rtx->shape->refl)
	, "reflection of a plane", 1)) : 0;
	if (buf[4] && buf[5] && buf[6] && !isnan(ft_atof(buf[6])))
		shape->dam = ft_atof(buf[6]);
	return (ret);
}

char		*pars_tr(char **buf, t_rtx *rtx)
{
	char *ret;
	t_tg *sh;

	sh = malloc(sizeof(t_tg));
	sh->next = rtx->shape;
	rtx->shape = sh;
	sh->type = 3;
	init_trd(sh);
	if (!buf[1] || !buf[2] || !buf[3] || !buf[4])
		return ("Missing argument(s) on declaraton of triangle");
	if (buf[5] != NULL && buf[6] != NULL && buf[7] != NULL && buf[8] != NULL)
		return ("Too many arguments on declaration of triangle");
	ret = read_pos(buf[1], &(sh->p1), "of triangle");
	ret = join(ret, read_pos(buf[2], &(sh->p2), "of triangle"));
	ret = join(ret, read_pos(buf[3], &(sh->p3), "of triangle"));
	ret = join(ret, read_color(buf[4], &(sh->color), " of triangle"));
	sh->normal = normalize(cross(min(sh->p2, sh->p1), min(sh->p3, sh->p1)));
	sh->center = sh->p1;
	ret = (buf[5]) ? join(ret, read_float(buf[5], &(sh->trans),
	" transparence of a triangle", 1)) : 0;
	ret = (buf[5] && buf[6]) ? join(ret, read_float(buf[6], &(sh->refl),
		" reflection of a triangle", 1)) : 0;
	if (buf[5] && buf[6] && buf[7] && !isnan(ft_atof(buf[7])))
		sh->dam = ft_atof(buf[7]);
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
	init_trd(shape);
	if (!buf[1] || !buf[2] || !buf[3] || !buf[4])
		return ("Missing argument(s) on declaraton of a square");
	if (buf[5] != NULL && buf[6] != NULL && buf[7] != NULL && buf[8] != NULL)
		return ("Too many arguments on declaration of a square");
	ret = read_pos(buf[1], &(shape->center), " of a square");
	ret = join(ret, read_vec(buf[2], &(shape->vec), " of a square"));
	ret = join(ret, read_float(buf[3], &(shape->hi), "height of a square", -1));
	ret = join(ret, read_color(buf[4], &(shape->color), " of a square"));
	ret = (buf[5]) ? join(ret, read_float(buf[5], &(shape->trans),
	"transparence of a square", 1)) : ret;
	ret = (buf[5] && buf[6]) ? join(ret, read_float(buf[6], &(shape->refl),
	"reflection of a square", 1)) : ret;
	if (buf[5] && buf[6] && buf[7] && !isnan(ft_atof(buf[7])))
		shape->dam = ft_atof(buf[7]);
	vec_tri(shape);
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
	init_trd(shape);
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
