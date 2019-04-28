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

void				free_fdf(fdf *elem)
{
    int i;

    i = 0;
    while (i < elem->lines)
    {
        free (elem->map[i]);
        i++;
    }
    free (elem->map);
}

int check_line(char *line)
{
    int i;
    int l;

    i = 0;
    l = 0;
    while (line[i])
    {
        if (ft_isdigit(line[i]))
        {
             l = 0;
        }
        else
        {
            if (line[i] != ' ' || l == 1)
                return (0);
            l = 1;
        }
        i++;
    }
    return (1);
}

int alloc_line(char *line, fdf *elem)
{
    int i;
    char **split;

    if (!check_line(line))
        return (0);
    i = 0;
    split = ft_strsplit(line,' ');
    while (split[i])
        i++;
    if (elem->numbers == 0)
        elem->numbers = i;
    else
    {
        if (i != elem->numbers)
            return (0);
    }
    free (split);
    elem->lines++;
    return (1);
    
}

int alloc_file(fdf *elem)
{
    int bytes;
    char *line;

    elem->lines = 0;
    elem->numbers = 0;
    while ((bytes = get_next_line(elem->fd, &line)) != 0)
    {
        if (!alloc_line(line, elem))
        {
            close (elem->fd);
            return (0);
        }
    }
    elem->map = (int **)malloc(sizeof(int *) * elem->lines);
    close (elem->fd);
    elem->fd = open(elem->name,O_RDONLY);
    return (1);
}

int reader(fdf *elem)
{
    int bytes;
    char *line;
    char **split;
    int i;
    int j;

    i = 0;
    if (!(alloc_file(elem)))
        return (0);
    while ((bytes = get_next_line(elem->fd, &line)) != 0)
    {
        j = 0;
        split = ft_strsplit(line,' ');
        elem->map[i] = (int *)malloc(sizeof(int) * elem->numbers);
        while (split[j])
        {
            elem->map[i][j] = ft_atoi(split[j]);
            free(split[j]);
            j++;
        }
        free(split);
        i++;
    }
    return(bytes == -1 ? 0 : 1);
}