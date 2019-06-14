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

int alloc_line(char *line, t_fdf *elem)
{
    int i;
    char **split;

    if (!check_line(line))
        return (0);
    i = 0;
    split = ft_strsplit(line,' ');
    while (split[i])
        i++;
    if (elem->width == 0)
        elem->width = i;
    else
    {
        if (i != elem->width)
            return (0);
    }
    free (split);
    elem->height++;
    return (1);
    
}

int validate_map(t_list **array_list)
{
	t_list	*tmp;
	size_t	len;

	if (*array_list)
	{
		tmp = *array_list;
		len = tmp->content_size;
		while (tmp)
		{
			if (tmp->content_size != len)
			{
				ft_memdel((void **) &tmp);
				return (0);
			}
			tmp = tmp->next;
		}
		return (1);
	}
	return (0);
}

static void	ft_lstcat(t_list **alst, t_list *new)
{
	t_list *scout;

	if (*alst && new)
	{
		scout = *alst;
		while (scout->next != NULL)
			scout = scout->next;
		scout->next = new;
	}
	else
		*alst = new;
}

static int *create_array(char **split, int size)
{
    int	*arr;
	int	i;

	i = 0;
	arr = ft_memalloc(sizeof(int) * size);
	while (i < size)
	{
		arr[i] = ft_atoi(split[i]);
		i++;
	}
	return (arr);
}

//lstreverse doesn't work for some reason, need to adjuct it in the future

void reader(t_list **array_list, int fd)
{
    char *line;
    char **split;
    int i;
    int *arr;

    *array_list = NULL;
    while (get_next_line(fd, &line))
    {
        i = 0;
        split = ft_strsplit(line,' ');
        while (split[i])
            i++;
        arr = create_array(split,i);
        ft_lstcat(array_list,ft_lstnew(arr,sizeof(int) * i));
        free(split);
        free(arr);
    }
    //ft_lstreverse(*array_list);
}