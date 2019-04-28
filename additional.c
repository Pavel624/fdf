/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbethany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 22:17:20 by nbethany          #+#    #+#             */
/*   Updated: 2019/04/19 20:17:22 by nbethany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void menu(fdf *elem)
{
    int y;

    y = 0;
    mlx_string_put(elem->mlx,elem->window, 15, y+=20, TEXT_COLOR, "Zoom: +/-");
    mlx_string_put(elem->mlx,elem->window, 15, y+=20, TEXT_COLOR, "Move: Arrow keys");
    mlx_string_put(elem->mlx,elem->window, 15, y+=20, TEXT_COLOR, "Rotate:");
    mlx_string_put(elem->mlx,elem->window, 15, y+=20, TEXT_COLOR, "X-Axis");
    mlx_string_put(elem->mlx,elem->window, 15, y+=20, TEXT_COLOR, "Y-Axis");
    mlx_string_put(elem->mlx,elem->window, 15, y+=20, TEXT_COLOR, "Z-Axis");
    mlx_string_put(elem->mlx,elem->window, 15, y+=20, TEXT_COLOR, "Exit: ESC");
}


int deal_key(int key, fdf *elem)
{
    if (key == 0xff1b)
        exit(EXIT_SUCCESS);
    return (0);
    elem->name = "lel";
}

void mlx_setup(fdf *elem)
{
    elem->mlx = mlx_init();
    elem->window = mlx_new_window(elem->mlx, WIDTH, HEIGHT, "FDF");
    menu(elem);
    draw_elem(elem);
    mlx_key_hook(elem->window,deal_key,elem);
    mlx_loop(elem->mlx);
}