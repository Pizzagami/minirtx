/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirtx.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 12:10:53 by selgrabl          #+#    #+#             */
/*   Updated: 2020/02/05 10:40:46 by braimbau         ###   ########.fr       */
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
#define CORE 4
#define StructureNotifyMask	(1L<<17)
#define DestroyNotify	17
#define NAF 42

t_color			cal_col(t_cam, t_rtx rtx, int bound);
t_color     	cal_lit(t_cam cam, t_tg shape, t_rtx *rtx, float dist);

void            *cal_cam(t_rtx *rtx, void *mlx_ptr, t_cam *cam);
void            multi_thread(t_cam *cam, t_rtx *rtx);
int				key_hook(int key, void *param);

int				exit_hook(void *param);

void			print_vec(t_vec vec);
void            *show(void *arg);
void			print_vecs(int nbr,...);

#endif

#define PREV_CAM 43
#define NEXT_CAM 47
#define RXU 125
#define RXD 126
#define RYU 124
#define RYD 123
#define RZU 121
#define RZD 117
#define TXU 0
#define TXD 2
#define TYU 12
#define TYD 14
#define TZU 1
#define TZD 13
#define FI_R 18
#define FI_G 19
#define FI_B 20
#define FI_Y 21
#define FI_P 23
#define FI_C 22
#define FI_N 26
#define FI_W 28
#define FI_S 25
#define FI_RST 29
#define QUA_UP 24
#define QUA_DO 27