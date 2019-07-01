/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbethany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 20:17:20 by nbethany          #+#    #+#             */
/*   Updated: 2019/04/16 20:17:22 by nbethany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

static t_point get_point(t_map *map, char *split, int row, int column)
{
    t_point point;

    point.x = (double) column;
    point.y = (double) row;
    point.z = (double) ft_atoi(split);
    point.w = 1;
    point.color = 0x00FFFFFF;
    if (point.z > map->max_z)
        map->max_z = point.z;
    if (point.z < map->min_z)
        map->min_z = point.z;
    return (point);
}

static int fill_struct(t_map *map, t_list *data)
{
    t_list *current_elem;
    int column;
    int row;
    char **split;

    current_elem = data;
    row = 0;
    map->max_z = 0;
    map->min_z = 0;
    while (row < map->height)
    {
        column = 0;
        split = ft_strsplit((char *) current_elem->content, ' ');
        while (column < map->width)
        {
            map->points[row * map->width + column] = get_point(map, split[column], row, column);
            column++;
        }
        row++;
        current_elem = current_elem->next;
    }
    return (1);
}

static int get_line(t_map *map, t_list **data, int fd)
{
    t_list *line_data;
    int bytes;
    char *line;

    line_data = NULL;
    while ((bytes = get_next_line(fd, &line) > 0))
    {
        if (map->width == 0)
            map->width = (int) ft_count_words(line, ' ');
        else if (map->width != (int) ft_count_words(line, ' '))
            return (0);
        line_data = ft_lstnew(line, ft_strlen(line) + 1);
        ft_lstadd(data,line_data);
        map->height++;
    }
    return (1);
}

int reader(t_map *array_list, int fd)
{
    t_list *map;

    map = NULL;
    array_list->height = 0;
    array_list->width = 0;
    if (!get_line(array_list,&map,fd))
        return (0);
    array_list->points = malloc(array_list->height * array_list->width * sizeof(t_point));
    array_list->xpoints = malloc(array_list->height * array_list->width * sizeof(t_point));
    return (fill_struct(array_list, map));
}