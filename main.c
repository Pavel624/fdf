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

void parser(fdf *elem)
{
    if (!reader(elem))
    {
        ft_putstr("error\n");
        exit(EXIT_SUCCESS);
    }
    else
    {
        ft_putstr("ok\n");
    }
    //fdf(elem);
}

int main(int argc, char *argv[])
{
    fdf elem;

    if (argc == 2)
    {
        elem.fd = open(argv[1],O_RDONLY);
        elem.name = argv[1];
        parser(&elem);
    }
    else
    {
        ft_putstr("usage: ./fdf input file\n");
        exit(EXIT_SUCCESS);
    }
    for (int i = 0; i < elem.lines; i++)
    {
        for (int j = 0; j < elem.numbers; j++)
        {
            printf("%d ",elem.map[i][j]);
        }
        printf("\n");
    }
    //if (elem.fd < 0)
    //{
    //    ft_putstr("invalid file name\n");
    //    exit(EXIT_SUCCESS);
    //}
    //elem.mlx = mlx_init();
    //elem.window = mlx_new_window(elem.mlx, WIDTH, HEIGHT, "Title");
    //mlx_loop(elem.mlx);
    return (0);
}
