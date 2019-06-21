/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbethany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 22:17:20 by nbethany          #+#    #+#             */
/*   Updated: 2019/04/27 20:17:22 by nbethany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int index_matr(int row, int column, int map_width)
{
    return (row * map_width + column);
}

static t_line set_line(t_point point_0, t_point point_1)
{
    t_line line;

    line.x0 = (int) point_0.x;
    line.y0 = (int) point_0.y;
    line.x1 = (int) point_1.x;
    line.y1 = (int) point_1.y;
    line.dx = ABS(line.x1 - line.x0);
    line.dy = ABS(line.y1 - line.y0);
    line.qx = line.x0 < line.x1 ? 1 : -1;
    line.qy = line.y0 < line.y1 ? 1 : -1;
    line.error = ((line.dx > line.dy) ? line.dx : -line.dy) / 2;
    line.color_grad = 0.0;
    return (line);
}

void		img_pixel_put(t_image *img, double x, double y, int color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		*(int *)(img->ptr + (int)(index_matr(y, x, WIDTH) * img->bpp)) = color;
}

void draw_line(t_fdf *elem, t_point point0, t_point point1)
{
    t_line line;

    line = set_line(point0,point1);
    while (1)
    {
        img_pixel_put(&elem->image, line.x0, line.y0, 0xffff);
        if (line.x0 == line.x1 && line.y0 == line.y1)
            break;
        line.error2 = line.error;
        if (line.error2 > -line.dx)
        {
			line.error -= line.dy;
			line.x0 += line.qx;
		}
		if (line.error2 < line.dy)
		{
			line.error += line.dx;
			line.y0 += line.qy;
		}
    }
}