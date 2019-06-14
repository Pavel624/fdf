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
    t_fdf *elem;
    int fd;
    t_list *array_list;

    array_list = NULL;
    elem = NULL;
    if (argc != 2)
        ft_error("usage: ./fdf *input_file*", 0);
    if ((fd = open(argv[1],O_RDONLY)) < 0)
        ft_error("File cannot be opened", 0);
    reader(&array_list,fd);
    if (!validate_map(&array_list))
        ft_error("Wrong file inputs", 0);
    elem = (t_fdf *)malloc(sizeof(t_fdf));
    if (!elem)
        ft_error("Memory allocation fail",0);
    elem = init_elem(array_list,argv[1]);

    mlx_key_hook(elem->window,deal_key,elem);
    mlx_expose_hook(elem->window,deal_key,elem);
    mlx_loop(elem->mlx);
    /*
    for (int i = 0; i < elem.height; i++)
    {
        for (int j = 0; j < elem.width; j++)
        {
            printf("%d ",elem.map[i][j]);
        }
        printf("\n");
    }
    free_fdf(&elem);
    */
    //elem.mlx = mlx_init();
    //elem.window = mlx_new_window(elem.mlx, WIDTH, HEIGHT, "Title");
    //mlx_loop(elem.mlx);
    return (0);
}
