/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 19:03:43 by selgrabl          #+#    #+#             */
/*   Updated: 2019/11/25 12:47:52 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

int main()
{
    void    *mlx_ptr;
    void    *mlx_win;
    int     x;
    int     y;
    float   dist;
    t_vec   ray;
    t_vec

    ray.x = -360;
    ray.y = 240;
    ray.z = 624;
    x = 0;
    mlx_ptr = mlx_init();
    mlx_win = mlx_new_window(mlx_ptr, 720, 480, "hello world");
    while(x++ < 720)
        {
            y = 0;
            while (y++ < 480)
            {
                dist = find_dist(ray, origin, center, int r);
            }
        }
    mlx_loop(mlx_ptr);
}
