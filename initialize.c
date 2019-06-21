/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbethany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 22:17:20 by nbethany          #+#    #+#             */
/*   Updated: 2019/06/18 20:17:22 by nbethany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void initialize_image(t_fdf *fdf)
{
    t_image *image;

    image = &fdf->image;

    image->image = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
    image->ptr = mlx_get_data_addr(image->image, &image->bpp, &image->line_s, &image->endian);
    image->bpp /= 8;
}