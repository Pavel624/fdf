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

//int check_line(char *line, int chars)
//{
    
//}

int check_file(fdf elem)
{
    int bytes;
    char *line;
    char **numbers;
    int i;
    int j;

    i = 0;
    while ((bytes = get_next_line(elem.fd, &line)) != 0)
    {
        j = i;
        while (bytes--)
            if (!ft_strchr("0123456789",line[bytes]))
                return (0);
        numbers = ft_strsplit(line,' ');
        while (numbers[i])
            i++;
    }
    elem.chars = i;
    close (elem.fd);
    return (1);
}

int reader(fdf elem)
{
    char *line;
    //char **numbers;
    //int bytes;
    //int chars;

    line = NULL;
    if (!(check_file(elem)))
        return (0);
    open(elem.name,O_RDONLY);
   // while (bytes = get_next_line(elem.fd, &line) != 0)
   // {
        //if (!check_line(line,chars))
        //    return (0);
   // }
    return(1);
}