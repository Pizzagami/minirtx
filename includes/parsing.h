/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raimbaultbrieuc <raimbaultbrieuc@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 13:36:32 by selgrabl          #+#    #+#             */
/*   Updated: 2020/01/24 15:46:56 by raimbaultbr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSING_H
# define PARSING_H

#include "tools.h"

int				increase_buf(char **buf);
int				is_sep(char c, char *sep);
int				get_next_line(int fd, char **line);
int				count_words(char *str, char *charset);
int				clear_buff(int x, int fd, char ***buf);

char			*pars_a(char **buf, t_rtx *rtx);
char			*pars_r(char **buf, t_rtx *rtx); 
char			*pars_c(char **buf, t_rtx *rtx); 
char			*pars_l(char **buf, t_rtx *rtx); 
char			*pars_s(char **buf, t_rtx *rtx);
char		    *pars_sm(char **buf, t_rtx *rtx);
char 			*pars_pl(char **buf, t_rtx *rtx);
char 			*pars_sq(char **buf, t_rtx *rtx); 
char			*pars_tr(char **buf, t_rtx *rtx); 
char			*pars_cy(char **buf, t_rtx *rtx); 
char			*pars_ce(char **buf, t_rtx *rtx); 
char			*pars_py(char **buf, t_rtx *rtx); 
char			*pars_cu(char **buf, t_rtx *rtx);
char		    *pars_aa(char **buf, t_rtx *rtx);

char			*ft_strcpy(char *dest, char *src);
char			**ft_split(char *str, char *charset);

void			corners(t_tg *shape);
void			find_vecs(t_tg *shape);
void			join2(char **line, char **buf, int x);
void			pars_sqr(int x, t_tg info, t_rtx *rtx);
void			ft_switch(char *buf, t_rtx *rtx, int fd, int i);
void			alloc_word(char *str, char *charset, char **ptr);

t_rtx			parsing(int fd, void* mlx_ptr);
t_rtx			parseke(int argc, char **argv, void* mlx_ptr);

#endif