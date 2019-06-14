/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbethany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 22:17:20 by nbethany          #+#    #+#             */
/*   Updated: 2019/04/27 20:17:22 by nbethany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
// Bresenham line drawing algorithm
*/

void bresenham_algorithm(t_fdf *elem, int x0, int y0, int x1, int y1)
{
    int	dx, dy;
    int temp, x, y;

	dx = x1 - x0;
	dy = y1 - y0;
    x = x0;
    y = y0;
    temp = 2 * dy - dx;
    while(x < x1)
	{
        if (temp < 0)
            temp += 2* dy;
        else
        {
            y++;
            temp += 2 * dy - 2 * dx;
        }
    mlx_pixel_put(elem->mlx, elem->window, x, y, TEXT_COLOR);
    x++;
    }
}


void draw_elem(t_fdf *elem)
{
    bresenham_algorithm(elem,100,100,500,300);
}