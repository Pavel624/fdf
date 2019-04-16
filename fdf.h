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

#include "libft.h"
#include <math.h>
#include "./minilibx/mlx.h"
#include <X11/Xlib.h>
#include <stdlib.h>
#include <fcntl.h>

typedef struct s_fdf
{
    int fd;
    void *mlx;
    void *window;
}               fdf;

void parser(fdf map);