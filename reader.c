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

static int validate_number(char *number)
{
	size_t len;

	len = (*number == '-' || *number == '+');
	while (len < ft_strlen(number))
	{
		if (!ft_isdigit(number[len]))
			return (0);
		len++;
	}
	return (1);
}

static	t_point	get_point(t_map *map, char *split, int row, int column)
{
	t_point	point;
	char	*number;

	number = split;
	point.x = (double)column;
	point.y = (double)row;
	if (!validate_number(number))
		ft_error("Something is wrong with file inputs", 0);
	point.z = (double)ft_atoi(split);
	point.color = 0xFFFFFF;
	if (point.z > map->max_z)
		map->max_z = point.z;
	if (point.z < map->min_z)
		map->min_z = point.z;
	return (point);
}

static	int		fill_struct(t_map *map, t_list *data)
{
	t_list	*current_elem;
	int		column;
	int		row;
	char	**split;

	current_elem = data;
	row = map->height - 1;
	map->max_z = -2147483648;
	map->min_z = 2147483647;
	while (row >= 0)
	{
		column = map->width - 1;
		split = ft_strsplit((char *)current_elem->content, ' ');
		while (column >= 0)
		{
			map->points[index_matr(row, column, map->width)] =
								get_point(map, split[column], row, column);
			column--;
		}
		row--;
		current_elem = current_elem->next;
	}
	return (1);
}

static	int		get_line(t_map *map, t_list **data, int fd)
{
	t_list	*line_data;
	int		bytes;
	char	*line;

	line_data = NULL;
	while ((bytes = get_next_line(fd, &line) > 0) && *line)
	{
		if (map->width == 0)
			map->width = (int)ft_count_words(line, ' ');
		else if (map->width != (int)ft_count_words(line, ' '))
			return (0);
		line_data = ft_lstnew(line, ft_strlen(line) + 1);
		ft_lstadd(data, line_data);
		map->height++;
	}
	return (1);
}

int				reader(t_map *fdf_map, int fd)
{
	t_list	*map;

	map = NULL;
	fdf_map->height = 0;
	fdf_map->width = 0;
	if (!get_line(fdf_map, &map, fd) || !map)
		return (0);
	fdf_map->points = malloc(fdf_map->height *
								fdf_map->width * sizeof(t_point));
	fdf_map->xpoints = malloc(fdf_map->height *
								fdf_map->width * sizeof(t_point));
	return (fill_struct(fdf_map, map));
}
