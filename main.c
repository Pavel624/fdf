/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbethany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 19:30:22 by nbethany          #+#    #+#             */
/*   Updated: 2019/04/12 19:30:52 by nbethany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

static void ft_error(char *msg, int i)
{
    ft_putstr(ft_strjoin(msg,"\n"));
    exit(i);
}

int main(int argc, char *argv[])
{
    t_fdf elem;
    int fd;

    if (argc != 2)
        ft_error("usage: ./fdf *input_file*", 0);
    if ((fd = open(argv[1],O_RDONLY)) < 0)
        ft_error("File cannot be opened", 0);
    if (!reader(&elem.map,fd))
        ft_error("Something is wrong with file inputs", 0);
    close(fd);
    init_elem(&elem, argv[1]);
    render_image(&elem);
    mlx_key_hook(elem.window, key_down, &elem);
    mlx_hook(elem.window, 2, 0, key_trans, &elem);
    mlx_hook(elem.window, 4, 0, mouse_trans_pressed, &elem);
    mlx_hook(elem.window, 5, 0, mouse_trans_released, &elem);
    mlx_hook(elem.window, 6, 0, mouse_trans_moved, &elem);
    mlx_loop((&elem)->mlx);
    return (0);
}
