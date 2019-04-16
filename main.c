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

#include <X11/Xlib.h>
#include "fdf.h"
#include <stdio.h>

//void parser(fdf map)
//{
   // if (!reader(map))
   // {
       // ft_putstr("error\n");
       // map.mlx = mlx_init();
        //exit(EXIT_SUCCESS);
   // }
    
//}

int main(int argc, char *argv[])
{
    fdf map;

    map.mlx = mlx_init();
   map.window = mlx_new_window(map.mlx, 1000, 1000, "Title");
   mlx_loop(map.mlx);
    if (argc != 2)
    {
        ft_putstr("usage: ./fdf input file\n");
        exit(EXIT_SUCCESS);
    }
    map.fd = open(argv[1],O_RDONLY);
    if (map.fd < 0)
    {
        ft_putstr("invalid file name\n");
        exit(EXIT_SUCCESS);
    }
   // else
      //  parser(map);

   
   // mlx_pixel_put (mlx, window, 100, 100, 255 );
   // mlx_loop(mlx);
    
    return (0);
}
