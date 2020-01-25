/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4transf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 17:30:11 by raimbaultbr       #+#    #+#             */
/*   Updated: 2020/01/25 14:17:40 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

void    make_rotation(int key, t_cam *cam)
{
    if (key == RXU)
		cam->rot.x += 0.05;
    if (key == RXD)
		cam->rot.x -= 0.05;
	if (key == RYU)
        cam->rot.y += 0.05;
    if (key == RYD)
        cam->rot.y -= 0.05;
	if (key == RZU)
		cam->rot.z += 0.05;
	if (key == RZD)
		cam->rot.z -= 0.05;
}

void    make_translation(int key, t_cam *cam)
{
	if (key == TXU)
		cam->origin = min(cam->origin, fois(cam->right, 5));
	if (key == TXD)
		cam->origin = plus(cam->origin, fois(cam->right, 5));
	if (key == TYU)
		cam->origin = min(cam->origin, fois(cam->up, 5));
	if (key == TYD)
		cam->origin = plus(cam->origin, fois(cam->up, 5));
	if (key == TZU)
		cam->origin = min(cam->origin, fois(cam->vec, 5));
	if (key == TZD)
		cam->origin = plus(cam->origin, fois(cam->vec, 5));
}

void	apply_filter(int key, t_cam *cam)
{
	if (key == FI_R && cam->filter != 'r')
		cam->filter = 'R';
	if (key == FI_G && cam->filter != 'r')
		cam->filter = 'G';
	if (key == FI_B && cam->filter != 'r')
		cam->filter = 'B';
	if (key == FI_P && cam->filter != 'r')
		cam->filter = 'P';
	if (key == FI_C && cam->filter != 'r')
		cam->filter = 'C';
	if (key == FI_Y && cam->filter != 'r')
		cam->filter = 'Y';
	if (key == FI_W && cam->filter != 'r')
		cam->filter = 'W';
	if (key == FI_N && cam->filter != 'r')
		cam->filter = 'N';
	if (key == FI_S && cam->filter != 'r')
		cam->filter = 'S';
	if (key == FI_RST)
		cam->filter = 0;
}