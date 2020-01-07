/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 17:26:19 by braimbau          #+#    #+#             */
/*   Updated: 2020/01/07 17:20:56 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

char	*read_float(char *str, float *value, char *id, float max)
{
	*value = ft_atof(str);
	if (isnan(*value))
		return(join("invalid value for ", id));
	if (*value < 0)
		return(join("Value out of range for ", id));
	if (max > 0 && *value > max)
		return(join("Value out of range for ", id));
	return (NULL);
}
