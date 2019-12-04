/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 13:36:32 by selgrabl          #+#    #+#             */
/*   Updated: 2019/12/04 13:05:23 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "tools.h"

t_rtx			parseke(int argc, char **argv);
t_rtx			parsing(int fd);
void			ft_switch(char buf[BUFFER_SIZE], t_rtx *rtx, int fd);
char			*init_ar(char buf[BUFFER_SIZE], int *x, t_rtx *rtx);
char			*init_view(char buf[BUFFER_SIZE], int *x, t_rtx *rtx);
char			*init_sp(char buf[BUFFER_SIZE], int *x, t_rtx *rtx);
char			*init_tc(char buf[BUFFER_SIZE], int *x, t_rtx *rtx);

#endif