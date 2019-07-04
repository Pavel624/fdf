/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbethany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 22:17:20 by nbethany          #+#    #+#             */
/*   Updated: 2019/04/19 20:17:22 by nbethany         ###   ########.fr       */
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
    mlx_string_put(elem->mlx,elem->window, pos+=20, HEIGHT - 30, TEXT_COLOR, "Zoom: Mouse wheel");
    mlx_string_put(elem->mlx,elem->window, pos+=220, HEIGHT - 30, TEXT_COLOR, "Move: Arrow keys");
    mlx_string_put(elem->mlx,elem->window, pos+=200, HEIGHT - 30, TEXT_COLOR, "Rotate:");
    mlx_string_put(elem->mlx,elem->window, pos+=130, HEIGHT - 60, TEXT_COLOR, "X-Axis");
    mlx_string_put(elem->mlx,elem->window, pos+=130, HEIGHT - 30, TEXT_COLOR, "[Q] [E]");
    mlx_string_put(elem->mlx,elem->window, pos+=130, HEIGHT - 60, TEXT_COLOR, "Y-Axis");
    mlx_string_put(elem->mlx,elem->window, pos, HEIGHT - 30, TEXT_COLOR, "[A] [D]");
    mlx_string_put(elem->mlx,elem->window, pos+=130, HEIGHT - 60, TEXT_COLOR, "Z-Axis");
    mlx_string_put(elem->mlx,elem->window, pos+=130, HEIGHT - 60, TEXT_COLOR, "[Z] [C]");
    mlx_string_put(elem->mlx,elem->window, pos+=130, HEIGHT - 30, TEXT_COLOR, "Exit: ESC");
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
    elem->x_scale = elem->scale;
    elem->y_scale = elem->scale;
    elem->z_scale = elem->scale;
}


void init_point(t_point *point)
{
    point->x = 0;
    point->y = 0;
    point->z = 0;
    point->w = 0;
    point->color = 0;
}

t_point multiplicate_matrixes(t_matrix matrix, t_point point)
{
    t_point new_point;
    int i;
    double *coord[4];

    init_point(&new_point);
    coord[0] = &new_point.x;
    coord[1] = &new_point.y;
    coord[2] = &new_point.z;
    coord[3] = &new_point.w;
    i = 0;
    while (i <= 2)
    {
        *coord[i] += matrix.value[index_matr(i, 0, 4)] * point.x;
		*coord[i] += matrix.value[index_matr(i, 1, 4)] * point.y;
		*coord[i] += matrix.value[index_matr(i, 2, 4)] * point.z;
		*coord[i] += matrix.value[index_matr(i, 3, 4)] * point.w;
		*coord[i + 1] += matrix.value[index_matr(i + 1, 0, 4)] * point.x;
		*coord[i + 1] += matrix.value[index_matr(i + 1, 1, 4)] * point.y;
		*coord[i + 1] += matrix.value[index_matr(i + 1, 2, 4)] * point.z;
		*coord[i + 1] += matrix.value[index_matr(i + 1, 3, 4)] * point.w;
		i += 2;
    }
    return (new_point);
}

void init_elem(t_fdf *elem, char* name)
{
    double x_scale;
    double y_scale;

    elem->name = name;
    elem->mlx = mlx_init();
    elem->window = mlx_new_window(elem->mlx, WIDTH, HEIGHT, "FDF");
    initialize_image(elem);
    init_mouse(elem);
    x_scale = WIDTH / elem->map.width;
    y_scale = HEIGHT / elem->map.height;
    elem->scale = x_scale > y_scale ? y_scale : x_scale;
    reset_fdf(elem);
    elem->color_max = 0xFF0000;
    elem->color_min = 0x0000FF;
}

t_point transform_point(t_fdf *fdf, t_map *map, int row, int column)
{
    t_point current_point;
    t_point new_point;
    double map_middle_z;
    double map_middle_x;
    double map_middle_h;

    map_middle_x = (double)((map->width - 1) / 2);
    map_middle_h = (double)((map->height - 1) / 2);
    map_middle_z = (double)(map->max_z - map->min_z) / 2;
    current_point = map->points[index_matr(row, column, map->width)];
    new_point = multiplicate_matrixes(translate(-map_middle_x, -map_middle_h, -map_middle_z), current_point);
    new_point = multiplicate_matrixes(scale(fdf->x_scale, fdf->y_scale, fdf->z_scale), new_point);
    new_point = multiplicate_matrixes(rotate_x(fdf->x_rotation, 0), new_point);
    new_point = multiplicate_matrixes(rotate_y(fdf->y_rotation, 0), new_point);
    new_point = multiplicate_matrixes(rotate_z(fdf->z_rotation, 0), new_point);
    new_point = multiplicate_matrixes(translate((WIDTH / 2), (HEIGHT / 2), 0), new_point);
    new_point = multiplicate_matrixes(translate(fdf->x_shift, fdf->y_shift, fdf->z_shift), new_point);
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

void		clear_img(t_image *img)
{
	ft_bzero(img->ptr, WIDTH * HEIGHT * img->bpp);
}

void render_image(t_fdf *fdf)
{
    t_point point;
    int row;
    int column;
    int map_w;

    clear_img(&fdf->image);
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
}
