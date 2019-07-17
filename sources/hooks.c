/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbethany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 22:17:20 by nbethany          #+#    #+#             */
/*   Updated: 2019/07/17 11:29:39 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int key_down(int key, t_fdf *fdf)
{
	if (key == KEY_ESC)
	{
		free_fdf(fdf);
		exit(EXIT_SUCCESS);
	}
	else if (key == KEY_P)
	{
		fdf->camera = PAR;
		reset_fdf(fdf);
	}
	else if (key == KEY_I)
	{
		fdf->camera = ISO;
		reset_fdf(fdf);
	}
	else if (key == KEY_NUMPAD_1)
	{
		fdf->color_max = 0xF5A142;
        fdf->color_mid = 0xF54275;
		fdf->color_min = 0x9042F5;
	}
	else if (key == KEY_NUMPAD_2)
	{
		fdf->color_max = 0xFFFFFF;
		fdf->color_mid = 0xFFFFFF;
		fdf->color_min = 0xFFFFFF;
	}
	else if (key == KEY_NUMPAD_3)
	{
		fdf->color_max = 0xFD00D0;
        fdf->color_mid = 0x3755CC;
		fdf->color_min = 0x00FF00;
	}
	else if (key == KEY_NUMPAD_4)
	{
		fdf->color_max = 0x8ED943;
        fdf->color_mid = 0x27E8B1;
		fdf->color_min = 0x2757E8;
	}
	render_image(fdf);
	return (0);
}

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
	else if (key == KEY_DOWN)
		fdf->y_shift += 5;
	else if (key == KEY_RIGHT)
		fdf->x_shift += 5;
	else if  (key == KEY_LEFT)
		fdf->x_shift -= 5;
	else if  (key == KEY_Q)
		fdf->x_rotation += 0.05;
	else if  (key == KEY_E)
		fdf->x_rotation -= 0.05;
	else if  (key == KEY_A)
		fdf->y_rotation += 0.05;
	else if  (key == KEY_D)
		fdf->y_rotation -= 0.05;
	else if  (key == KEY_Z)
		fdf->z_rotation += 0.05;
	else if  (key == KEY_C)
		fdf->z_rotation -= 0.05;
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
	else if (button == 4 && fdf->scale - 2 >= 0)
		fdf->scale -= 2;
	else if  (button == 5)
		fdf->scale += 2;
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
		fdf->x_rotation -= (mouse->y0 - y) / 180;
		fdf->y_rotation += (mouse->x0 - x) / 180;
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