/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 17:51:24 by nboste            #+#    #+#             */
/*   Updated: 2017/03/10 04:47:05 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandelbrot.h"
#include "drawer.h"

/*static uint32	get_color(double ratio)
  {
  return ((int)(0xFF * ratio) << 8);
  }*/

void	init_mandelbrot(t_frac_gen *gen)
{
	gen->max.x = 0.6;
	gen->max.y = 1.2;
	gen->min.x = -2.1;
	gen->min.y = -1.2;
	gen->it = 200;
	gen->base_it = 200;
	gen->current = mandelbrot;
}

void	process_mandelbrot(t_3dvertex *point, t_frac_gen *gen)
{
	t_2dpair		z;
	t_2dpair		tmp;
	int			i;

	i = 0;
	z.x = 0;
	z.y = 0;
	while ((z.x * z.x + z.y * z.y) <= 4 && i < gen->it)
	{
		tmp = z;
		z.x = (z.x * z.x) - (z.y * z.y) + point->x;
		z.y = 2 * tmp.x * z.y + point->y;
		i++;
	}
	point->z = -i;
}
