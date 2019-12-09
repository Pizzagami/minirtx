/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirtx.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 12:10:53 by selgrabl          #+#    #+#             */
/*   Updated: 2019/12/09 17:58:51 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRTX_H
# define MINIRTX_H

#include <mlx.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "struct.h"
#include "parsing.h"

#define BUFFER_SIZE 42
#define StructureNotifyMask	(1L<<17)
#define DestroyNotify	17
#define NAF M_E

t_color			cal_col(t_cam, t_rtx rtx);
t_color     	cal_lit(t_cam cam, t_tg shape, t_rtx rtx, float dist);
int				key_hook(int key);
int				exit_hook(void *param);

#endif