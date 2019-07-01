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
#include <stdio.h>
# define WIDTH 1000
# define HEIGHT 1000
# define TEXT_COLOR 0xEAEAEA

# define KEY_ESC 53

# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124

# define KEY_ZOOM_IN 69
# define KEY_ZOOM_OUT 78

# define KEY_NUM_4 86
# define KEY_NUM_6 88
# define KEY_NUM_7 89
# define KEY_NUM_9 92

# define KEY_R 15

typedef struct s_point
{
    double x;
    double y;
    double z;
    double w;
    int color;
}              t_point;

typedef struct s_line
{
    int x0;
    int y0;
    int x1;
    int y1;
    int dx;
    int dy;
    int qx;
    int qy;
    int error;
    int error2;
    double color_grad; 
    int color;
}               t_line;

typedef struct s_plot
{
    int x1;
    int x2;
    int y1;
    int y2;
    int z1;
    int z2;
    struct s_plot *next; 
}              t_plot;

typedef struct s_max_min
{
    int x_max;
    int x_min;
    int y_max;
    int y_min;
    int z_max;
    int z_min;
}               t_max_min;

typedef struct s_matrix
{
    int column;
    int row;
    double value[16];
}               t_matrix;

typedef struct s_image 
{
    void *image;
    char *ptr;
    int bpp;
    int line_s;
    int endian;
}               t_image;

typedef struct s_map
{
    int width;
    int height;
    int max_z;
    int min_z;
    t_point *points;
    t_point *xpoints;
}               t_map;

typedef struct s_mouse
{
    double x;
    double y;
    double x0;
    double y0;
    int pressed;
}               t_mouse;

typedef struct s_fdf
{
    char *name;
    t_map map;
    void *mlx;
    void *window;
    t_image image;
    t_mouse mouse;
    double x_scale;
    double y_scale;
    double z_scale;
    double x_rotation;
    double y_rotation;
    double z_rotation;
    double x_shift;
    double y_shift;
    double z_shift;
    int color_max;
    int color_min;
    int color_style;
}               t_fdf;

/*
// reader.c
*/
int reader(t_map *array_list, int fd);
int validate_map(t_map *array_list);

/*
// matrixes.c
*/

t_matrix    scale(double x_scale, double y_scale, double z_scale);
t_matrix    translate(double x_trans, double y_trans, double z_trans);
t_matrix	rotate_z(double theta, int key);
t_matrix	rotate_y(double theta, int key);
t_matrix	rotate_x(double theta, int key);

void init_elem(t_fdf *elem, char* name);

int key_down(int key, t_fdf *fdf);
int key_trans(int key, t_fdf *fdf);
int mouse_trans_pressed(int button, int x, int y, t_fdf *fdf);
int mouse_trans_moved(int x, int y, t_fdf *fdf);
int mouse_trans_released(int button, int x, int y, t_fdf *fdf);
void init_mouse(t_fdf *fdf);

void reset_fdf(t_fdf *elem);

void menu(t_fdf *elem);

int calculate_color(t_fdf *fdf, t_map *map, t_point point);
void clear_image(t_fdf *fdf, t_image *image);
void mlx_setup(t_fdf *elem);
int deal_key(int key, t_fdf *elem);
void draw_line(t_fdf *elem, t_point point_0, t_point point_1);
void initialize_image(t_fdf *fdf);
void render_image(t_fdf *fdf);
void		img_pixel_put(t_image *img, double x, double y, int color);
int index_matr(int row, int column, int map_width);

#endif