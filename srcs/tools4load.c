/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4load.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 17:00:10 by braimbau          #+#    #+#             */
/*   Updated: 2020/01/13 11:01:32 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

void	refresh_loading_bar(void *mlx_ptr, void	*mlx_win, int pourcentage)
{
	void	*img;
	char	*id;
	int		x;
	int y;

	img = mlx_new_image(mlx_ptr, 5, 50);
	id = mlx_get_data_addr(img, &x, &x, &x);

	x = 0;
	while (x < 5)
	{
		y = 0;
		while (y < 50)
		{
			id[(x + y * 5) * 4] = ((x + y + pourcentage * 5) / 50 % 2 == 0) ? (char)252 : (char)45;
			id[(x + y * 5) * 4 + 1] = ((x + y + pourcentage * 5) / 50 % 2 == 0) ? (char)142 : (char)45;
			id[(x + y * 5) * 4 + 2] = ((x + y + pourcentage * 5) / 50 % 2 == 0) ? (char)45 : (char)252;
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(mlx_ptr, mlx_win, img, 50 + pourcentage * 5, 0);
	mlx_string_put(mlx_ptr, mlx_win, 15, 30, 0, join(ft_itoa(pourcentage - 1), "%"));
	mlx_string_put(mlx_ptr, mlx_win, 15, 30, 16777215, join(ft_itoa(pourcentage), "%"));
	mlx_do_sync(mlx_ptr);
}