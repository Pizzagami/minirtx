/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:07:13 by selgrabl          #+#    #+#             */
/*   Updated: 2020/02/05 14:02:54 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

char		*pars_cy(char **buf, t_rtx *rtx)
{
	char	*ret;
	t_tg	*shape;

	shape = malloc(sizeof(t_tg));
	shape->next = rtx->shape;
	rtx->shape = shape;
	shape->type = 2;
	init_trd(shape);
	if (!buf[1] || !buf[2] || !buf[3] || !buf[4] || !buf[5])
		return ("Missing argument(s) on declaraton of cylinder");
	if (buf[6] != NULL && buf[7] != NULL && buf[8] != NULL && buf[9] != NULL)
		return ("Too many arguments on declaration of cylinder");
	ret = read_pos(buf[1], &(shape->center), " of cylinder");
	ret = join(ret, read_vec(buf[2], &(shape->vec), " of cylinder"));
	shape->dia = ft_atof(buf[3]);
	ret = (isnan(shape->dia) || shape->dia < 0) ?
	join(ret, "Invalid value for diameter of a cylinder") : ret;
	ret = pars_cy2(shape, rtx, buf, ret);
	return (ret);
}

char		*pars_cy2(t_tg *shape, t_rtx *rtx, char **buf, char *ret)
{
	float	x;

	x = 0;
	shape->hi = ft_atof(buf[4]);
	ret = (isnan(shape->hi) || shape->hi < 0) ? join(ret,
	"Invalid value for high of cylinder") : ret;
	ret = join(ret, read_color(buf[5], &(shape->color), " of cylinder"));
	ret = (buf[6]) ? join(ret, read_float(buf[6], &(shape->trans),
	" transparence of a cylinder", 1)) : ret;
	ret = (buf[6] && buf[7]) ? join(ret, read_float(buf[7], &(shape->refl),
	" reflection of a cylinder", 1)) : ret;
	if (buf[6] && buf[7] && buf[8])
		ret = join(ret, read_float(buf[8], &x, "capuchon of a cylinder", -1));
	shape->vec = normalize(shape->vec);
	(x == 1) ? creat_ce(*shape, rtx) : ret;
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
	init_trd(shape);
	if (!buf[1] || !buf[2] || !buf[3] || !buf[4] || !buf[5])
		return ("Missing argument(s) on declaraton of cone");
	if (buf[6] != NULL)
		return ("Too many arguments on declaration of cone");
	ret = read_pos(buf[1], &(shape->center), " of cone");
	ret = join(ret, read_vec(buf[2], &(shape->vec), " of cone"));
	shape->dia = ft_atof(buf[3]);
	ret = (isnan(shape->dia) || shape->dia < 0 || shape->dia > 90) ?
	join(ret, "Invalid value for angle of cone") : 0;
	shape->hi = ft_atof(buf[4]);
	ret = (isnan(shape->hi) || shape->hi < 0) ? join(ret,
	"Invalid value for high of cone") : 0;
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
	init_trd(shape);
	if (!buf[1] || !buf[2] || !buf[3] || !buf[4] || !buf[5])
		return ("Missing argument(s) on declaraton of sablier");
	ret = (!buf[6]) ? ("Too many arguments on declaration of sablier") : 0;
	ret = read_pos(buf[1], &(shape->center), " of sablier");
	ret = join(ret, read_vec(buf[2], &(shape->vec), " of sablier"));
	shape->dia = ft_atof(buf[3]);
	shape->hi = ft_atof(buf[4]);
	ret = (isnan(shape->dia) || shape->dia < 0 || shape->dia > 90) ? join(ret,
	"Invalid value for angle of sablier") : ret;
	ret = (isnan(shape->hi) || shape->hi < 0) ? join(ret,
	"Invalid value for high of sablier") : ret;
	ret = join(ret, read_color(buf[5], &(shape->color), " of sablier"));
	shape->vec = normalize(shape->vec);
	shape->dia *= M_PI / 180;
	return (ret);
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
