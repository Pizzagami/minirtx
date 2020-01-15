/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirtx.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 12:10:53 by selgrabl          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2020/01/13 22:25:02 by selgrabl         ###   ########.fr       */
=======
/*   Updated: 2020/01/13 11:05:28 by braimbau         ###   ########.fr       */
>>>>>>> master
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
#include <stdarg.h>
#include "struct.h"
#include "parsing.h"
#include <pthread.h>


#define BUFFER_SIZE 42
#define StructureNotifyMask	(1L<<17)
#define DestroyNotify	17
#define NAF 42

t_color			cal_col(t_cam, t_rtx rtx, int bound);
t_color     	cal_lit(t_cam cam, t_tg shape, t_rtx *rtx, float dist);
void            *cal_cam(t_rtx *rtx, void *mlx_ptr, void *mlx_win_load, t_cam *cam);
int				key_hook(int key, void *param);

int				exit_hook(void *param);

void			print_vec(t_vec vec);
void			print_vecs(int nbr,...);

#endif