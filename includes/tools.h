/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 13:32:33 by selgrabl          #+#    #+#             */
/*   Updated: 2020/01/25 14:19:41 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

#include "minirtx.h"

int	            nb_char(long n);
int				ft_atoi(char *str);
int				ft_strlen(char *str);
int     		distri(t_tg tri, t_vec p);
int				ft_strcmp(char *s1, char *s2);
int				distce(t_tg shape, t_vec dot);
int     		distsqr(t_tg shape, t_vec   dot);
int				second_degre(float a, float b, float c, float *x1, float *x2);

char		    *ft_itoa(int n);
char			*check_ligne(char *str);
char			*join(char *s1, char *s2);
char			*strjoin(int nbr, char *s1, ...);
char			*read_vec(char *buf, t_vec *vec, char *id);
char			*read_pos(char *buf, t_vec *vec, char *id);
char			*read_color(char *buf, t_color *color,char *str);
char            *read_float(char *str, float *value, char *id, float max);

float      		ft_atof(char *buf);
float			dot(t_vec machin, t_vec bidule);
float   		dist_dot(t_vec machin, t_vec bidule);
float			find_dist(t_vec origin, t_vec ray, t_tg *shape);
float			find_dist_sp(t_vec   origin, t_vec ray, t_tg shape);
float			find_dist_stcp(t_vec   origin, t_vec ray, t_tg shape);
float			find_dist_cy(t_vec   origin, t_vec ray, t_tg *shape, t_vec pos);
float			find_dist_co(t_vec origin, t_vec ray, t_tg *shape, t_vec pos);
float			find_dist_sa(t_vec origin, t_vec ray, t_tg *shape, t_vec pos);
float	        cal_lite_inter(t_rtx rtx, t_light *li, t_vec point, t_tg shape);

void			ft_putnbr(int nb);
void			ft_putstr(char *str);
void			init_lst(t_rtx *rtx);
void			tri_vecs(t_tg *shape);
void            make_mapping(t_tg *shape);
void            make_3d(t_cam **ca, t_res res);
void	        apply_filter(int key, t_cam *cam);
void            make_rotation(int key, t_cam *cam);
void	        export_to_bmp(char *id, t_res res);
void            make_translation(int key, t_cam *cam);
void            anti_aliesing(t_cam *cam, t_rtx *rtx);
void            filter(char filter, t_res res, char **id);
void            create_tri(t_vec p1, t_vec p2, t_vec p3, t_rtx *rtx);
void			damier(t_vec point, t_tg *shape, t_color *color, float dist);
void			mlx_put_pixel_img(int x, int y, char **id, int sl, t_color color);
void            refresh_loading_bar(t_rtx *rtx, void	*mlx_win, int pourcentage);

t_vec			normalize(t_vec vect);
t_vec			fois(t_vec truc, float a);
t_vec			min(t_vec truc, t_vec machin);
t_vec			plus(t_vec truc, t_vec machin);
t_vec           vec_matrixed(t_vec v, t_matrix m);
t_vec			cross(t_vec machin, t_vec bidule);
t_vec		    init_vec(float x, float y, float z);

t_color			lfois(t_color color, float a);
t_color			color_init(int r, int g, int b);
t_color         cp(int x, int y, char *id, t_res res);
t_color			color_cap(t_color color, t_color max);
t_color         cosha(float ratio, t_color light, t_color shape);
t_color			color_add(t_color base, t_color add, float coef);
t_color		    cm(t_color c1, t_color c2, t_color c3, t_color c4);
t_color         color_mix(t_color c1, t_color c2, float r1, float r2);

t_matrix        init_matrix(t_vec a, t_vec b, t_vec c);

#endif
