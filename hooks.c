/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbethany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 18:18:22 by nbethany          #+#    #+#             */
/*   Updated: 2019/07/01 18:34:50 by nbethany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void init_mouse(t_fdf *fdf)
{
    t_mouse *mouse;

    mouse = &fdf->mouse;
    mouse->pressed = 0;
    mouse->x0 = 0;
    mouse->y0 = 0;
    mouse->x = 0;
    mouse->y = 0;

}

int key_trans(int key, t_fdf *fdf)
{
    if (key == KEY_UP)
        fdf->y_shift -= 5;
    if (key == KEY_DOWN)
        fdf->y_shift += 5;
    if (key == KEY_RIGHT)
        fdf->x_shift += 5;
    if (key == KEY_LEFT)
        fdf->x_shift -= 5;
    if (key == 83)
	{
		fdf->z_rotation += (2 * M_PI / 360);
		fdf->z_rotation = fmod(fdf->z_rotation, 360);
	}
	if (key == 85)
	{
		fdf->z_rotation -= (2 * M_PI / 360);
		fdf->z_rotation = fmod(fdf->z_rotation, 360);
	}
    render_image(fdf);
    return (0);
}

int mouse_trans_pressed(int button, int x, int y, t_fdf *fdf)
{
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
    {
        if (button == 1)
        {
            (&fdf->mouse)->x = x;
            (&fdf->mouse)->y = y;
            (&fdf->mouse)->pressed = 1;
        }
        if (button == 4 && fdf->x_scale > 0 && fdf->y_scale > 0 && fdf->z_scale > 0)
        {
            fdf->x_scale -= 3;
            fdf->y_scale -= 3;
            fdf->z_scale -= 3;
        }
        if (button == 5)
        {
            fdf->x_scale += 3;
            fdf->y_scale += 3;
            fdf->z_scale += 3;
        }
        render_image(fdf);
    }
    return (0);
}

int mouse_trans_moved(int x, int y, t_fdf *fdf)
{
    t_mouse *mouse;

    mouse = &fdf->mouse;
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
    {
        mouse->x0 = mouse->x;
        mouse->y0 = mouse->y;
        mouse->x = x;
        mouse->y = y;
        if (mouse->pressed)
        {
            fdf->x_rotation += (mouse->y0 - y) / 150;
            fdf->y_rotation -= (mouse->x0 - x) / 150;
        }
        if (mouse->pressed)
            render_image(fdf);
    }
    return (0);
}

int mouse_trans_released(int button, int x, int y, t_fdf *fdf)
{
    t_mouse *mouse;
    mouse = &fdf->mouse;
    (void) button;
    (void) x;
    (void) y;
    mouse->pressed = 0;
    return (0);
}
