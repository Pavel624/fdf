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

void parser(fdf elem)
{
    if (!reader(elem))
    {
        ft_putstr("error\n");
        exit(EXIT_SUCCESS);
    }
}

int main(int argc, char *argv[])
{
    fdf elem;

    if (argc != 2)
    {
        ft_putstr("usage: ./fdf input file\n");
        exit(EXIT_SUCCESS);
    }
    elem.fd = open(argv[1],O_RDONLY);
    elem.name = argv[1];
    if (elem.fd < 0)
    {
        ft_putstr("invalid file name\n");
        exit(EXIT_SUCCESS);
    }
    parser(elem);
    elem.mlx = mlx_init();
    elem.window = mlx_new_window(elem.mlx, 1000, 1000, "Title");
    mlx_loop(elem.mlx);
    return (0);
}
