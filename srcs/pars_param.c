/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:27:44 by selgrabl          #+#    #+#             */
/*   Updated: 2020/02/03 16:11:51 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char		*pars_a(char **buf, t_rtx *rtx)
{
	char	*ret;

	if (!buf[1] || !buf[2])
		return ("Missing argument(s) on declaraton of ambiant light");
	if (buf[3] != NULL)
		return ("Too many arguments on declaration of ambiant light");
	rtx->amb.ratio = ft_atof(buf[1]);
	if ((isnan(rtx->amb.ratio)))
		return ("Invalid number for ratio of ambiant light");
	if (rtx->amb.ratio > 1 || rtx->amb.ratio < 0)
		return ("Value out of range for ratio of ambiant light");
	ret = read_color(buf[2], &(rtx->amb.color), "of ambiant light");
	rtx->amb.color = lfois(rtx->amb.color, rtx->amb.ratio);
	return (ret);
}

char		*pars_r(char **buf, t_rtx *rtx)
{
	if (!buf[1] || !buf[2])
		return ("Missing argument(s) on declaraton of resolution");
	if (buf[3] != NULL)
		return ("Too many arguments on declaration of resolution");
	rtx->res.x = ft_atoi(buf[1]);
	rtx->res.y = ft_atoi(buf[2]);
	if (rtx->res.x == -42)
		return ("Invalid number for x of resolution");
	if (rtx->res.x < 0)
		return ("Value out of range for x of resolution");
	if (rtx->res.y == -42)
		return ("Invalid number for y of resolution");
	if (rtx->res.y < 0)
		return ("Value out of range for y of resolution");
	if (rtx->res.x < rtx->res.y)
		return ("X/Y must be supperior to 1");
	return (NULL);
}

char		*pars_c(char **buf, t_rtx *rtx)
{
	char	*ret;
	t_cam	*cam;

	cam = malloc(sizeof(t_cam));
	cam->next = rtx->cam;
	rtx->cam = cam;
	cam->filter = 0;
	if (!buf[1] || !buf[2] || !buf[3])
		return ("Missing argument(s) on declaraton of camera");
	if (buf[4] != NULL && buf[5] != NULL)
		return ("Too many arguments on declaration of camera");
	ret = read_pos(buf[1], &(rtx->cam->origin), "of camera");
	ret = join(ret, read_vec(buf[2], &(rtx->cam->vec), "of camera"));
	cam->vec = fois(normalize(cam->vec), -1);
	cam->right = normalize(cross(cam->vec, init_vec(0, 1, 0)));
	if (isnan(cam->right.x) && isnan(cam->right.z) && isnan(cam->right.y))
		cam->right = (cam->vec.y > 0) ? init_vec(1, 0, 0) : init_vec(-1, 0, 0);
	cam->up = fois(normalize(cross(cam->right, cam->vec)), -1);
	rtx->cam->fov = ft_atoi(buf[3]);
	ret = (cam->fov > 180 || cam->fov < 0) ? join(ret,
	"Invalid number for FOV of camera"): 0;
	ret = (buf[4]) ? pars_3d(buf, rtx, ret, cam) : ret;
	cam->rot = init_vec(0, 0, 0);
	return (ret);
}

char		*pars_l(char **buf, t_rtx *rtx)
{
	char	*ret;
	t_light	*light;

	light = malloc(sizeof(t_light));
	light->next = rtx->light;
	rtx->light = light;
	light->para = init_vec(0, 0, 0);
	if (!buf[1] || !buf[2] || !buf[3])
		return ("Missing argument(s) on declaraton of light");
	if (buf[4] != NULL && buf[5] != NULL)
		return ("Too many arguments on declaration of light");
	ret = read_pos(buf[1], &(light->pos), "of light");
	light->ratio = ft_atof(buf[2]);
	if (isnan(light->ratio))
		return ("Invalid number for ratio of light");
	if (light->ratio > 1 || light->ratio < 0)
		return ("Value out of range for ratio of light");
	ret = join(ret, read_color(buf[3], &(rtx->light->color), "of light"));
	rtx->light->color = lfois(rtx->light->color, rtx->light->ratio);
	if (buf[4])
		ret = read_vec(buf[4], &(light->para), "vector of parallel light");
	return (ret);
}

char		*pars_3d(char **buf, t_rtx *rtx, char *ret, t_cam *cam)
{
	if (buf[4][0] == '3' && buf[4][1] == 'D' && buf[4][2] == 0)
	{
		cam->origin.x -= 2;
		cam->filter = 'l';
		buf[4][0] = 'r';
		buf[4][1] = 0;
		pars_c(buf, rtx);
	}
	else if ((buf[4][0] == 'R' || buf[4][0] == 'G' || buf[4][0] == 'B' ||
	buf[4][0] == 'C' || buf[4][0] == 'Y' || buf[4][0] == 'P' || buf[4][0]
	== 'W' || buf[4][0] == 'N' || buf[4][0] == 'S' || buf[4][0] == 'r')
	&& buf[4][1] == 0)
	{
		cam->filter = buf[4][0];
	}
	else
		return (join(ret, "Invalid value for filter of camera"));
	return(NULL);
}