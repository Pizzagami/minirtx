/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 13:50:48 by selgrabl          #+#    #+#             */
/*   Updated: 2020/02/06 15:55:48 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include "minirtx.h"

void	make_mapping(t_tg *shape);
void	make_3d(t_cam **ca, t_res res);
void	apply_filter(int key, t_cam *cam);
void	make_rotation(int key, t_cam *cam);
void	export_to_bmp(char *id, t_res res);
void	make_translation(int key, t_cam *cam);
void	anti_aliasing(t_cam *cam, t_rtx *rtx);
void	put_pixel(t_res r, char **id, int sl, t_color color);
t_vec	cal_pix(t_thread *tt, float pw, float ph);

#endif
