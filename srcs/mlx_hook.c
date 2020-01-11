/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:53:33 by braimbau          #+#    #+#             */
/*   Updated: 2020/01/11 18:33:50 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

int		exit_hook(void *param)
{
	(void)param;
	exit(0);
	return(EXIT_SUCCESS);
}

int		key_hook(int key)
{
	if (key == 53)
		exit(0);
	return(EXIT_SUCCESS);
}

void	mlx_put_pixel_img(int x, int y, char **id, int sl, t_color color)
{
	(*id)[(x + (y * sl)) * 4] = (char)color.b;
	(*id)[((x + (y * sl)) * 4) + 1] = (char)color.g;
	(*id)[((x + (y * sl)) * 4 )+ 2] = (char)color.r;
}
