/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrixes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbethany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 22:17:20 by nbethany          #+#    #+#             */
/*   Updated: 2019/06/19 20:17:22 by nbethany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_matrix scale(double x_scale, double y_scale, double z_scale)
{
    t_matrix scale_matrix;

    ft_bzero((void *)&scale_matrix,sizeof(scale_matrix));
    scale_matrix.value[index_matr(0, 0, 4)] = x_scale;
    scale_matrix.value[index_matr(1, 1, 4)] = y_scale;
    scale_matrix.value[index_matr(2, 2, 4)] = z_scale;
    scale_matrix.value[index_matr(3, 3, 4)] = 1;
    return (scale_matrix);
}

t_matrix translate(double x_trans, double y_trans, double z_trans)
{
    t_matrix scale_matrix;

    ft_bzero((void *)&scale_matrix,sizeof(scale_matrix));
    scale_matrix.value[index_matr(0, 0, 4)] = 1;
    scale_matrix.value[index_matr(1, 1, 4)] = 1;
    scale_matrix.value[index_matr(2, 2, 4)] = 1;
    scale_matrix.value[index_matr(3, 3, 4)] = 1;
    scale_matrix.value[index_matr(0, 3, 4)] = x_trans;
    scale_matrix.value[index_matr(1, 3, 4)] = y_trans;
    scale_matrix.value[index_matr(2, 3, 4)] = z_trans;
    return (scale_matrix);
}

t_matrix	rotate_z(double theta, int key)
{
	t_matrix trans_matrix;

    ft_bzero((void *)&trans_matrix,sizeof(trans_matrix));
	trans_matrix.value[index_matr(0, 0, 4)] = cos(theta);
	trans_matrix.value[index_matr(0, 1, 4)] = (key) ? -sin(theta) : sin(theta);
	trans_matrix.value[index_matr(1, 0, 4)] = (key) ? sin(theta) : -sin(theta);
	trans_matrix.value[index_matr(1, 1, 4)] = cos(theta);
	trans_matrix.value[index_matr(2, 2, 4)] = 1;
	trans_matrix.value[index_matr(3, 3, 4)] = 1;
	return (trans_matrix);
}

t_matrix	rotate_y(double theta, int key)
{
	t_matrix trans_matrix;

    ft_bzero((void *)&trans_matrix,sizeof(trans_matrix));
	trans_matrix.value[index_matr(0, 0, 4)] = cos(theta);
	trans_matrix.value[index_matr(0, 2, 4)] = (key) ? sin(theta) : -sin(theta);
	trans_matrix.value[index_matr(1, 1, 4)] = 1;
	trans_matrix.value[index_matr(2, 0, 4)] = (key) ? -sin(theta) : sin(theta);
	trans_matrix.value[index_matr(2, 2, 4)] = cos(theta);
	trans_matrix.value[index_matr(3, 3, 4)] = 1;
	return (trans_matrix);
}

t_matrix	rotate_x(double theta, int key)
{
	t_matrix trans_matrix;

    ft_bzero((void *)&trans_matrix,sizeof(trans_matrix));
	trans_matrix.value[index_matr(0, 0, 4)] = 1;
	trans_matrix.value[index_matr(1, 1, 4)] = cos(theta);
	trans_matrix.value[index_matr(1, 2, 4)] = (key) ? -sin(theta) : sin(theta);
	trans_matrix.value[index_matr(2, 1, 4)] = (key) ? sin(theta) : -sin(theta);
	trans_matrix.value[index_matr(2, 2, 4)] = cos(theta);
	trans_matrix.value[index_matr(3, 3, 4)] = 1;
	return (trans_matrix);
}
