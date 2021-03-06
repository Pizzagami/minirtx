/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_dist.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 13:46:42 by selgrabl          #+#    #+#             */
/*   Updated: 2020/02/06 15:55:54 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIND_DIST_H
# define FIND_DIST_H

# include "minirtx.h"

int		distri(t_tg tri, t_vec p);
int		distce(t_tg shape, t_vec dot);
int		distsqr(t_tg shape, t_vec dot);
float	find_dist(t_vec origin, t_vec ray, t_tg *shape);
float	find_dist_sp(t_vec origin, t_vec ray, t_tg shape);
float	find_dist_stcp(t_vec origin, t_vec ray, t_tg shape);
float	find_dist_t(t_vec origin, t_vec ray, t_tg *shape, t_vec pos);
float	find_dist_cy(t_vec origin, t_vec ray, t_tg *shape, t_vec pos);
float	find_dist_co(t_vec origin, t_vec ray, t_tg *shape, t_vec pos);

#endif
