/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbethany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 19:30:59 by nbethany          #+#    #+#             */
/*   Updated: 2019/04/12 19:33:15 by nbethany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>
#include "./minilibx/mlx.h"
#include <stdlib.h>
#include <fcntl.h>
#define WIDTH 1920
#define HEIGHT 1080

typedef struct s_fdf
{
    int fd;
    char *name;
    int **map;
    int lines;
    int numbers;
    void *mlx;
    void *window;
}               fdf;

void parser(fdf *elem);
int reader(fdf *elem);
int alloc_file(fdf *elem);
int alloc_line(char *line, fdf *elem);
int check_line(char *line);