/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 17:30:11 by selgrabl          #+#    #+#             */
/*   Updated: 2020/02/06 15:57:32 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

void	make_rotation(int key, t_cam *cam)
{
	if (key == RXU)
		cam->rot.x += 0.051;
	if (key == RXD)
		cam->rot.x -= 0.051;
	if (key == RYU)
		cam->rot.y += 0.051;
	if (key == RYD)
		cam->rot.y -= 0.051;
	if (key == RZU)
		cam->rot.z += 0.051;
	if (key == RZD)
		cam->rot.z -= 0.051;
}

void	make_translation(int key, t_cam *cam)
{
	if (key == TXU)
		cam->origin = plus(cam->origin, fois(cam->right, 5.1));
	if (key == TXD)
		cam->origin = min(cam->origin, fois(cam->right, 5.1));
	if (key == TYU)
		cam->origin = plus(cam->origin, fois(cam->up, 5.1));
	if (key == TYD)
		cam->origin = min(cam->origin, fois(cam->up, 5.1));
	if (key == TZU)
		cam->origin = plus(cam->origin, fois(cam->vec, 5.1));
	if (key == TZD)
		cam->origin = min(cam->origin, fois(cam->vec, 5.1));
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
