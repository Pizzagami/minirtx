/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 13:36:32 by braimbau          #+#    #+#             */
/*   Updated: 2020/02/06 10:34:01 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

int		increase_buf(char **buf);
int		is_sep(char c, char *sep);
int		get_next_line(int fd, char **line);
int		count_words(char *str, char *charset);
int		clear_buff(int x, int fd, char ***buf);
char	*pars_a(char **buf, t_rtx *rtx);
char	*pars_r(char **buf, t_rtx *rtx);
char	*pars_c(char **buf, t_rtx *rtx);
char	*pars_l(char **buf, t_rtx *rtx);
char	*pars_s(char **buf, t_rtx *rtx);
char	*pars_sm(char **buf, t_rtx *rtx);
char	*pars_pl(char **buf, t_rtx *rtx);
char	*pars_sq(char **buf, t_rtx *rtx);
char	*pars_tr(char **buf, t_rtx *rtx);
char	*pars_cy(char **buf, t_rtx *rtx);
char	*pars_co(char **buf, t_rtx *rtx);
char	*pars_sa(char **buf, t_rtx *rtx);
char	*pars_ce(char **buf, t_rtx *rtx);
char	*pars_py(char **buf, t_rtx *rtx);
char	*pars_cu(char **buf, t_rtx *rtx);
char	*pars_aa(char **buf, t_rtx *rtx);
char	*pars_3d(char **buf, t_rtx *rtx, char *ret, t_cam *cam);
char	*pars_cy2(t_tg *shape, t_rtx *rtx, char **buf, char *ret);
void	vec_tri(t_tg *shape);
void	corners(t_tg *shape);
void	init_trd(t_tg *shape);
void	find_vecs(t_tg *shape);
void	face_py(t_tg *shape, t_rtx *rtx);
void	creat_ce(t_tg shape, t_rtx *rtx);
void	join2(char **line, char **buf, int x);
void	pars_sqr(int x, t_tg info, t_rtx *rtx);
void	ft_switch(char *buf, t_rtx *rtx, int fd, int i);
void	create_tri(t_vec p1, t_vec p2, t_vec p3, t_rtx *rtx);
t_rtx	parsing(int fd, void *mlx_ptr);
t_rtx	parseke(int argc, char **argv, void *mlx_ptr);

#endif
