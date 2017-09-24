/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 17:59:36 by nboste            #+#    #+#             */
/*   Updated: 2017/09/24 08:50:51 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "julia.h"
#include "drawer.h"

void	init_julia(t_frac_gen *gen)
{
	gen->max.x = 1;
	gen->max.y = 1.2;
	gen->min.x = -1;
	gen->min.y = -1.2;
	gen->it = 200;
	gen->base_it = 200;
	gen->current = julia;
}

void	process_julia(t_3dvertex *point, t_frac_gen *gen)
{
	t_2dpair		z;
	t_2dpair		tmp;
	int				i;

	i = 0;
	z.x = point->x;
	z.y = point->y;
	point->x = 0.285;
	point->y = 0.01;
	while ((z.x * z.x + z.y * z.y) <= 4 && i < gen->it)
	{
		tmp = z;
		z.x = (z.x * z.x) - (z.y * z.y) + point->x;
		z.y = 2 * tmp.x * z.y + point->y;
		i++;
	}
	point->z = -i;
}
