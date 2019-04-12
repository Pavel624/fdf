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
#include "libft.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    int fd;
    void *mlx;
    void *window;

    if (argc != 2)
    {
        ft_putstr("usage: ./fdf input file\n");
        exit(EXIT_SUCCESS);
    }
    fd = open(argv[1],O_RDONLY);
    if (fd < 0)
    {
        ft_putstr("invalid file name\n");
        exit(EXIT_SUCCESS);
    }

    mlx = mlx_init();
    window = mlx_new_window(mlx, 1000, 1000, "Title");
    mlx_pixel_put (mlx, window, 100, 100, 255 );
    mlx_loop(mlx);
    
    return (0);
}
