/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirtx.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 12:10:53 by selgrabl          #+#    #+#             */
/*   Updated: 2019/12/07 17:23:40 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRTX_H
# define MINIRTX_H
 
#define BUFFER_SIZE 2147483
#include <mlx.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "struct.h"
#include "parsing.h"

#define StructureNotifyMask	(1L<<17)
#define DestroyNotify	17
#define NAF M_E

t_color			cal_col(t_cam, t_tg *lshape, t_light *llight,t_rtx rtx);
t_color     	cal_lit(t_cam cam, t_tg shape, t_rtx rtx, float dist);
int				key_hook(int key);
int				exit_hook(void *param);

#endif