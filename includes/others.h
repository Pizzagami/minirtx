/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 13:32:33 by selgrabl          #+#    #+#             */
/*   Updated: 2020/02/06 15:56:13 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTHERS_H
# define OTHERS_H

# include "minirtx.h"

int		nb_char(long n);
int		ft_atoi(char *str);
int		ft_strlen(char *str);
int		ft_strcmp(char *s1, char *s2);
char	*ft_itoa(int n);
char	*join(char *s1, char *s2);
char	*strjoin(int nbr, char *s1, ...);
char	*ft_strcpy(char *dest, char *src);
char	**ft_split(char *str, char *charset);
char	*read_vec(char *buf, t_vec *vec, char *id);
char	*read_pos(char *buf, t_vec *vec, char *id);
char	*read_color(char *buf, t_color *color, char *str);
char	*read_float(char *str, float *value, char *id, float max);
float	ft_atof(char *buf);
void	ft_putnbr(int nb);
void	ft_putstr(char *str);
void	free_buf(char **buf);
void	init_lst(t_rtx *rtx);
void	alloc_word(char *str, char *charset, char **ptr);
void	free_lists(t_cam *cam, t_light *light, t_tg *shape);

#endif
