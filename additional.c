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

void menu(t_fdf *elem)
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


int deal_key(int key, t_fdf *elem)
{
    if (key == 53)
        exit(EXIT_SUCCESS);
    return (0);
    elem->name = "lel";
}

t_fdf *init_elem(t_list *array_list,char *name)
{
    t_fdf *elem;

    elem = (t_fdf *)malloc(sizeof(t_fdf));
    elem->mlx = mlx_init();
    elem->window = mlx_new_window(elem->mlx, WIDTH, HEIGHT, name);
    elem->map=array_list;
    return(elem);
}

void mlx_setup(t_fdf *elem)
{
    
    menu(elem);
    draw_elem(elem);
    mlx_key_hook(elem->window,deal_key,elem);
    mlx_loop(elem->mlx);
}