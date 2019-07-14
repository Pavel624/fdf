/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   fdf.h  :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nbethany <marvin@42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2019/04/12 19:30:59 by nbethany  #+##+# */
/*   Updated: 2019/04/12 19:33:15 by nbethany ###   ########.fr   */
/**/
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "./libft/libft.h"
# include <math.h>
# include "./minilibx/mlx.h"
# include <stdlib.h>
# include <fcntl.h>
# define WIDTH 1600
# define HEIGHT 900
# define MENU_WIDTH 200
# define TEXT_COLOR 0xFFFFFF
# define BACKGROUND_COLOR 0x000000
# define MENU_BACKGROUND_COLOR 0x202020

# define KEY_ESC 53

# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124

# define KEY_ZOOM_IN 69
# define KEY_ZOOM_OUT 78

# define KEY_NUMPAD_1 83
# define KEY_NUMPAD_2 84
# define KEY_NUMPAD_3 85
# define KEY_NUMPAD_4 86

# define KEY_R 15
# define KEY_Q 12
# define KEY_E 14
# define KEY_A 0
# define KEY_D 2
# define KEY_Z 6
# define KEY_C 8
# define KEY_P 35
# define KEY_I 34

# define ISO 0
# define PAR 1

typedef struct s_point
{
int x;
int y;
int z;
int color;
}  t_point;

typedef struct s_line
{
int x0;
int y0;
int x1;
int y1;
int dx;
int dy;
int sx;
int sy;
int error;
int error2;
double color_grad;
int color;
}   t_line;

typedef struct s_matrix
{
double value[16];
}		t_matrix;

typedef struct s_image
{
void *image;
char *ptr;
int bpp;
int line_s;
int endian;
}		t_image;

typedef struct s_map
{
int width;
int height;
int max_z;
int min_z;
t_point *points;
t_point *xpoints;
}   t_map;

typedef struct s_mouse
{
double x;
double y;
double x0;
double y0;
int pressed;
}				t_mouse;

typedef struct s_fdf
{
t_map map;
void *mlx;
void *window;
t_image image;
t_mouse mouse;
int coord[WIDTH * HEIGHT];
double x_rotation;
double y_rotation;
double z_rotation;
int x_shift;
int y_shift;
int z_shift;
int scale;
char camera;
int color_max;
int color_min;
int color_style;
}   t_fdf;

/*
// main.c
*/

void		ft_error(char *msg, int i);

/*
// reader.c
*/

int			reader(t_map *array_list, int fd);

/*
// matrixes.c
*/

/*
// colors.c
*/

double		get_percentage_color(double start, double end, double current);
int			get_pixel_color(double start, double end, double current);
int			get_line_color(int color1, int color2, double color_grad);
int			calculate_color(t_fdf *fdf, t_map *map, t_point point);

/*
// image.c
*/

void		img_pixel_put(t_image *img, double x, double y, int color);
void		initialize_image(t_fdf *fdf);

void init_elem(t_fdf *elem, char* name);

void free_fdf(t_fdf *fdf);
int key_down(int key, t_fdf *fdf);
int key_trans(int key, t_fdf *fdf);
int mouse_trans_pressed(int button, int x, int y, t_fdf *fdf);
int mouse_trans_moved(int x, int y, t_fdf *fdf);
int mouse_trans_released(int button, int x, int y, t_fdf *fdf);
void init_mouse(t_fdf *fdf);

void reset_fdf(t_fdf *elem);

void menu(t_fdf *elem);

void init_buf(t_fdf *fdf);
void clear_background(t_image *img);
void clear_image(t_fdf *fdf, t_image *image);
void mlx_setup(t_fdf *elem);
int deal_key(int key, t_fdf *elem);
void draw_line(t_fdf *elem, t_point point_0, t_point point_1);
void render_image(t_fdf *fdf);
int index_matr(int row, int column, int map_width);

#endif
