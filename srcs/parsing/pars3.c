/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:38:19 by selgrabl          #+#    #+#             */
/*   Updated: 2020/02/06 15:58:31 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

char		*pars_s(char **buf, t_rtx *rtx)
{
	char *ret;
	t_tg *shape;

	shape = malloc(sizeof(t_tg));
	shape->next = rtx->shape;
	rtx->shape = shape;
	shape->type = 1;
	init_trd(shape);
	if (!(buf[1] || buf[2] || buf[3]))
		return ("Missing argument(s) on declaraton of a sphere");
	if (buf[4] != NULL && buf[5] != NULL && buf[6] != NULL && buf[7] != NULL)
		return ("Too many arguments on declaration of a sphere");
	ret = read_pos(buf[1], &(rtx->shape->center), " of a sphere");
	ret = join(ret, read_float(buf[2], &(shape->dia), " diameter of a sphere",
	-1));
	ret = join(ret, read_color(buf[3], &(shape->color), " of a sphere"));
	if (buf[4])
		ret = join(ret, read_float(buf[4], &(shape->trans),
		" transparence of a sphere", 1));
	if (buf[4] && buf[5])
		ret = join(ret, read_float(buf[5], &(shape->refl),
		" reflection of a sphere", 1));
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
	init_trd(shape);
	shape->v1 = init_vec(0, -1, 0);
	shape->v2 = init_vec(-1, 0, 0);
	if (!(buf[1] || buf[2] || buf[3]))
		return ("Missing argument(s) on declaraton of a mapped sphere");
	if (buf[4] != NULL)
		return ("Too many arguments on declaration of a mapped sphere");
	ret = read_pos(buf[1], &(rtx->shape->center), " of a mapped sphere");
	ret = join(ret, read_float(buf[2], &(shape->dia),
	" diameter of a mapped sphere", -1));
	map_ptr = mlx_xpm_file_to_image(rtx->mlx_ptr, buf[3], &(shape->map_res.x),
	&(shape->map_res.y));
	shape->map_id = mlx_get_data_addr(map_ptr, &x, &x, &x);
	return (ret);
}

char		*pars_py(char **buf, t_rtx *rtx)
{
	char	*ret;
	t_tg	*shape;

	shape = malloc(sizeof(t_tg));
	shape->next = rtx->shape;
	rtx->shape = shape;
	shape->type = 4;
	init_trd(shape);
	if (!buf[1] || !buf[2] || !buf[3] || !buf[4] || !buf[5])
		return ("Missing argument(s) on declaraton of a pyramide");
	if (buf[6] != NULL && buf[7] != NULL && buf[8] != NULL)
		return ("Too many arguments on declaration of a pyramide");
	ret = read_pos(buf[1], &(shape->center), " of a pyramide");
	ret = join(ret, read_vec(buf[2], &(shape->vec), " of a pyramide"));
	ret = join(ret, read_float(buf[3], &(shape->hi), "height of pyramide", -1));
	ret = join(ret, read_float(buf[4], &(shape->dia), "side of pyramide", -1));
	ret = join(ret, read_color(buf[5], &(shape->color), " of a pyramide"));
	ret = (buf[6]) ? join(ret, read_float(buf[6], &(shape->trans),
		"transparence of a pyramide", 1)) : ret;
	ret = (buf[6] && buf[7]) ? join(ret, read_float(buf[7], &(shape->refl),
		"reflection of a pyramide", 1)) : ret;
	vec_tri(shape);
	face_py(shape, rtx);
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
	shape->trans = info.trans;
	shape->refl = info.refl;
	shape->vec = (abs(x) == 2) ? info.v1 : info.vec;
	shape->v1 = (abs(x) == 2) ? info.vec : info.v1;
	shape->v2 = (abs(x) == 2) ? info.v2 : info.v2;
	shape->vec = (abs(x) == 3) ? info.v2 : shape->vec;
	shape->v1 = (abs(x) == 3) ? info.vec : shape->v1;
	shape->v2 = (abs(x) == 3) ? info.v1 : shape->v2;
	shape->center = (x > 0) ? plus(info.center, fois(shape->vec, info.hi / 2))
	: plus(info.center, fois(shape->vec, -info.hi / 2));
	corners(shape);
	tri_vecs(shape);
	shape->vec = normalize(cross(min(shape->p2, shape->p1),
		min(shape->p3, shape->p1)));
	shape->normal = shape->vec;
}
