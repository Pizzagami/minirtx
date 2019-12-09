/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:07:13 by selgrabl          #+#    #+#             */
/*   Updated: 2019/12/09 18:21:42 by selgrabl         ###   ########.fr       */
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
	int x;

	x = 0;
	if (!buf[1] || !buf[2])
		return("Missing argument(s) on declaraton of the resolution");
	if (buf[3])
		return("Too many arguments on declaration of the resolution");
	rtx->res.x = ft_atoi(buf[1], x);
	rtx->res.y = ft_atoi(buf[2], x);

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