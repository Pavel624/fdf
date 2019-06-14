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
# define WIDTH 1920
# define HEIGHT 1080
# define TEXT_COLOR 0xEAEAEA

# define KEY_ESC 53

# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124

# define KEY_ZOOM_IN 69
# define KEY_ZOOM_OUT 78

typedef struct s_fdf
{
    char *name;
    t_list *map;
    int height;
    int width;
    void *mlx;
    void *window;
}               t_fdf;

void parser(t_fdf *elem);
void reader(t_list **array_list, int fd);
int validate_map(t_list **array_list);
t_fdf *init_elem(t_list *array_list,char *name);
int alloc_file(t_fdf *elem);
int alloc_line(char *line, t_fdf *elem);
int check_line(char *line);
void free_fdf(t_fdf *elem);
void mlx_setup(t_fdf *elem);
int deal_key(int key, t_fdf *elem);
void draw_elem(t_fdf *elem);
void menu(t_fdf *elem);
void bresenham_algorithm(t_fdf *elem, int x0, int y0, int x1, int y1);

#endif