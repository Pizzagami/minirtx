/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:07:13 by selgrabl          #+#    #+#             */
/*   Updated: 2019/12/09 18:46:59 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char 		*pars_a(char **buf, t_rtx *rtx)
{
	if (!buf[1] || !buf[2])
		return("Missing argument(s) on declaraton of ambiant light");
	if (buf[3] != NULL)
		return("Too many arguments on declaration of ambiant light");
	rtx->amb.ratio = ft_atof(buf[1], 0);
	if (rtx->amb.ratio > 1 || rtx->amb.ratio < 0)
		return ("Value out of range for ratio of ambiant light");
	return(NULL);	
}

char		*pars_r(char **buf, t_rtx *rtx)
{
	if (!buf[1] || !buf[2])
		return("Missing argument(s) on declaraton of the resolution");
	if (buf[3])
		return("Too many arguments on declaration of the resolution");
	rtx->res.x = ft_atoi(buf[1], 0);
	if (rtx->res.x < 1 || rtx->res.x > 2160)
		return("Resolution in x out of range");
	rtx->res.y = ft_atoi(buf[2], 0);
	if (rtx->res.y < 1 || rtx->res.y > 1080)
		return("Resolution in y out of range");
	rtx->res.y = ft_atoi(buf[2], 0);

}

char 		*pars_sq(char **buf, t_rtx *rtx)
{
	return NULL;
}

char		*pars_s(char **buf, t_rtx *rtx)
{
	return NULL;
}

char		*pars_tr(char **buf, t_rtx *rtx)
{
	return NULL;
}

char		*pars_c(char **buf, t_rtx *rtx)
{
	return NULL;
}

char		*pars_l(char **buf, t_rtx *rtx)
{
	return NULL;
}

char		*pars_cy(char **buf, t_rtx *rtx)
{
	return NULL;
}

char		*pars_ce(char **buf, t_rtx *rtx)
{
	return NULL;
}

char		*pars_py(char **buf, t_rtx *rtx)
{
	return NULL;
}

char		*pars_cu(char **buf, t_rtx *rtx)
{
	return NULL;
}