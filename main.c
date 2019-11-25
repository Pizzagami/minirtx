/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 19:03:43 by selgrabl          #+#    #+#             */
/*   Updated: 2019/11/25 17:47:41 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirtx.h"

int find_dist(t_vec ray, t_vec origin, t_vec center, int r)
{
    float x1;
    float x2;
    int s;
    int mlp;

    s = second_degre(dot(ray, ray), 2 * dot(ray, min(origin, center)), dot(min(origin, center), min(origin, center)) - pow(r, 2), &x1, &x2);
    if (s == 1 && x1 > 0)
        return (rgbtoon(52, 201, 36, (x1 - 400) / 100 ));
    if (s == 2 && x2 > 0)
        return (rgbtoon(52, 201, 36, (x2 - 400) / 100 ));
    return (rgbtoon(3, 34, 76, 0));
}

int rgbtoon(int r, int g, int b, float o)
{
    int ret;
    r = r + (1 - r) * o;
    g = g + (1 - g) * o;
    b = b + (1 - b) * o;
    return(r * 65536 + g * 256 + b);
}

int main()
{
    void    *mlx_ptr;
    void    *mlx_win;
    int     x;
    int     y;
    float   color;
    t_vec   ray;
    t_vec   origin;
    t_vec   center;
    int r = 100;
    
    ray.z = 623.5;
    center.x = 0;
    center.y = 0;
    center.z = 500;
    origin.x = 0;
    origin.y = 0;
    origin.z = 0;

    x = -361;
    mlx_ptr = mlx_init();
    mlx_win = mlx_new_window(mlx_ptr, 720, 480, "hello world");
    while(x++ < 360)
        {
            ray.x = x;
            y = -241;
            while (y++ < 240)
            {
                ray.y = y;
                color = find_dist(normalize(ray), origin, center, r);
                mlx_pixel_put(mlx_ptr, mlx_win, x + 360, y + 240, color);
            }
        }
    mlx_loop(mlx_ptr);
}
