/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbethany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 22:17:20 by nbethany          #+#    #+#             */
/*   Updated: 2019/07/15 21:15:48 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int index_matr(int row, int column, int map_width)
{
	return (row * map_width + column);
}

void menu(t_fdf *elem)
{
	int pos;

	pos = 0;
	mlx_string_put(elem->mlx,elem->window, 15, pos+=20, TEXT_COLOR, "Zoom: Mouse wheel");
	mlx_string_put(elem->mlx,elem->window, 15, pos+=20, TEXT_COLOR, "Move: Arrow keys");
	mlx_string_put(elem->mlx,elem->window, 65, pos+=30, TEXT_COLOR, "Rotate:");
	mlx_string_put(elem->mlx,elem->window, 15, pos+=20, TEXT_COLOR, "X-Axis");
	mlx_string_put(elem->mlx,elem->window, 15, pos+=20, TEXT_COLOR, "[Q] [E] MOUSE1");
	mlx_string_put(elem->mlx,elem->window, 15, pos+=20, TEXT_COLOR, "Y-Axis");
	mlx_string_put(elem->mlx,elem->window, 15, pos+=20, TEXT_COLOR, "[A] [D] MOUSE1");
	mlx_string_put(elem->mlx,elem->window, 15, pos+=20, TEXT_COLOR, "Z-Axis");
	mlx_string_put(elem->mlx,elem->window, 15, pos+=20, TEXT_COLOR, "[Z] [C]");
	mlx_string_put(elem->mlx,elem->window, 15, pos+=30, TEXT_COLOR, "Change projection:");
	mlx_string_put(elem->mlx,elem->window, 15, pos+=20, TEXT_COLOR, "Parallel");
	mlx_string_put(elem->mlx,elem->window, 15, pos+=20, TEXT_COLOR, "[P]");
	mlx_string_put(elem->mlx,elem->window, 15, pos+=20, TEXT_COLOR, "Isometric");
	mlx_string_put(elem->mlx,elem->window, 15, pos+=20, TEXT_COLOR, "[I]");
	mlx_string_put(elem->mlx,elem->window, 15, pos+=30, TEXT_COLOR, "Change colors:");
	mlx_string_put(elem->mlx,elem->window, 15, pos+=20, TEXT_COLOR, "NUMPAD [1 - 4]");
	mlx_string_put(elem->mlx,elem->window, 15, pos+=30, TEXT_COLOR, "Exit: ESC");
}

void free_fdf(t_fdf *fdf)
{
	//free(&(fdf->map).xpoints);
	//free(fdf->map);
	mlx_destroy_image(fdf->mlx, fdf->image.image);
}

void reset_fdf(t_fdf *elem)
{
	elem->x_rotation = 0;
	elem->y_rotation = 0;
	elem->z_rotation = 0;
	elem->x_shift = 0;
	elem->y_shift = 0;
	elem->z_shift = 0;
}

void init_coord(t_fdf *fdf)
{
	int i;

	i = (int) WIDTH * HEIGHT;
    while (--i > -1)
    {
        if (i % WIDTH < MENU_WIDTH)
            i -= MENU_WIDTH - 1;
        fdf->coord[i] = -2147483648;
    }
}

void init_elem(t_fdf *elem, char* name)
{
	double x_scale;
	double y_scale;
	int    *image;

    int    i = WIDTH * HEIGHT;
	(void) name;
	elem->mlx = mlx_init();
	elem->window = mlx_new_window(elem->mlx, WIDTH, HEIGHT, "FDF");
	initialize_image(elem);
	init_mouse(elem);
	init_coord(elem);
	x_scale = (WIDTH - MENU_WIDTH) / elem->map.width / 2;
	y_scale = HEIGHT / elem->map.height / 2;
	elem->scale = x_scale > y_scale ? y_scale : x_scale;
	elem->camera = ISO;
	reset_fdf(elem);
	elem->color_max = 0xFFA500;
	elem->color_min = 0xE75480;
	image = (int *)(elem->image.ptr);
	while (--i > -1)
    {
	    if (i % WIDTH < MENU_WIDTH)
	        image[i] = MENU_BACKGROUND_COLOR;
	    else
	        i -= WIDTH - MENU_WIDTH - 1;
    }
}

static void iso(int *x, int *y, int z)
{
    int previous_x;
    int previous_y;

    previous_x = *x;
    previous_y = *y;
    *x = (previous_x - previous_y) * cos(0.523599);
    *y = -z + (previous_x + previous_y) * sin(0.523599);
}

static void	rotate_x_around(int *y, int *z, double alpha)
{
	int previous_y;

	previous_y = *y;
	*y = previous_y * cos(alpha) + *z * sin(alpha);
	*z = -previous_y * sin(alpha) + *z * cos(alpha);
}

static void	rotate_y_around(int *x, int *z, double beta)
{
	int previous_x;

	previous_x = *x;
	*x = previous_x * cos(beta) + *z * sin(beta);
	*z = -previous_x * sin(beta) + *z * cos(beta);
}

static void	rotate_z_around(int *x, int *y, double gamma)
{
	int previous_x;
	int previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = previous_x * cos(gamma) - previous_y * sin(gamma);
	*y = previous_x * sin(gamma) + previous_y * cos(gamma);
}

static void scale_point(t_point *point, t_fdf *fdf)
{
	int previous_x;
	int previous_y;
	int previous_z;

	previous_x = point->x;
	previous_y = point->y;
	previous_z = point->z;
	point->x = previous_x * fdf->scale;
	point->y = previous_y * fdf->scale;
	point->z = previous_z * fdf->scale;
}

static void translate_point(t_point *point, int x_shift, int y_shift, int z_shift)
{
	int previous_x;
	int previous_y;
	int previous_z;

	previous_x = point->x;
	previous_y = point->y;
	previous_z = point->z;
	point->x = previous_x + x_shift;
	point->y = previous_y + y_shift;
	point->z = previous_z + z_shift;
}

t_point transform_point(t_fdf *fdf, t_map *map, int row, int column)
{
	t_point current_point;
	t_point new_point;
	double map_middle_z;
	double map_middle_x;
	double map_middle_h;

	map_middle_x = (map->width - 1) / 2;
	map_middle_h = (map->height - 1) / 2;
	map_middle_z = (map->max_z - map->min_z) / 2;
	new_point = map->points[index_matr(row, column, map->width)];
	current_point = new_point;
	translate_point(&new_point, -map_middle_x, -map_middle_h, -map_middle_z);
	scale_point(&new_point, fdf);
	rotate_x_around(&new_point.y, &new_point.z,fdf->x_rotation);
	rotate_y_around(&new_point.x, &new_point.z,fdf->y_rotation);
	rotate_z_around(&new_point.x, &new_point.y,fdf->z_rotation);
	if (fdf->camera == ISO)
		iso(&new_point.x, &new_point.y, new_point.z);
	translate_point(&new_point,(WIDTH + MENU_WIDTH) / 2, HEIGHT / 2, 0);
	translate_point(&new_point, fdf->x_shift, fdf->y_shift, fdf->z_shift);
	new_point.color = calculate_color(fdf, map, current_point);
	return (new_point);
}

void put_pixels(t_fdf *fdf)
{
	t_point point;
	int row;
	int column;
	int map_w;

	row = fdf->map.height;
	map_w = fdf->map.width;
	while (--row > -1)
	{
		column = map_w;
		while (--column > -1)
		{
			point = transform_point(fdf, &fdf->map, row, column);
			fdf->map.xpoints[index_matr(row, column, map_w)] = point;
			img_pixel_put(&fdf->image, point.x, point.y, point.color);
		}
	}
}

void		clear_background(t_image *img)
{
	int i;
	int *image;

	image = (int *)(img->ptr);
	i = HEIGHT * WIDTH;
	while (--i > -1)
	{
        if (i % WIDTH < MENU_WIDTH)
            i -= MENU_WIDTH - 1;
        image[i] = BACKGROUND_COLOR;
    }
}

void render_image(t_fdf *fdf)
{
	t_point point;
	int row;
	int column;
	int map_w;

	clear_background(&fdf->image);
	init_coord(fdf);
	put_pixels(fdf);
	row = fdf->map.height;
	map_w = fdf->map.width;
	while (--row > -1)
	{
		column = map_w;
		while (--column > -1)
		{
			point = fdf->map.xpoints[index_matr(row, column, map_w)];
			if (row + 1 < fdf->map.height)
				draw_line(fdf, point, fdf->map.xpoints[index_matr(row + 1, column, map_w)]);
			if (column + 1 < map_w)
				draw_line(fdf, point, fdf->map.xpoints[index_matr(row, column + 1, map_w)]);
		}
	}
	mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->image.image, 0, 0);
    menu(fdf);
}
