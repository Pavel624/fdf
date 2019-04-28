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

#ifndef FDF_H
# define FDF_H

# include "./libft/libft.h"
# include <math.h>
# include "./minilibx/mlx.h"
# include <stdlib.h>
# include <fcntl.h>
# define WIDTH 1080
# define HEIGHT 1920
# define TEXT_COLOR 0xEAEAEA

typedef struct s_fdf
{
    int fd;
    char *name;
    int **map;
    int lines;
    int numbers;
    void *mlx;
    void *window;
    void *new_window;
}               fdf;

void parser(fdf *elem);
int reader(fdf *elem);
int alloc_file(fdf *elem);
int alloc_line(char *line, fdf *elem);
int check_line(char *line);
void free_fdf(fdf *elem);
void mlx_setup(fdf *elem);
int deal_key(int key, fdf *elem);
void draw_elem(fdf *elem);
void menu(fdf *elem);
void bresenham_algorithm(fdf *elem, int x0, int y0, int x1, int y1);

#endif