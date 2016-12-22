/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 17:51:24 by nboste            #+#    #+#             */
/*   Updated: 2016/12/21 13:45:40 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandelbrot.h"
#include "drawer.h"

static uint32	get_color(double ratio)
{
	return ((int)(0xFF * ratio) << 8);
}

void	init_mandelbrot(t_frac_gen *gen)
{
	gen->max.x = 0.6;
	gen->max.y = 1.2;
	gen->min.x = -2.1;
	gen->min.y = -1.2;
	gen->camera.pos.x = (gen->max.x - gen->min.x) / 2;
	gen->camera.org.x = (gen->max.x - gen->min.x) / 2;
	gen->camera.pos.y = (gen->max.y - gen->min.y) / 2;
	gen->camera.org.y = (gen->max.y - gen->min.y) / 2;
	gen->camera.zoom = 100;
	gen->it = 200;
	gen->base_it = 200;
}

void	process_mandelbrot(t_2ipair c, t_2dpair point, t_env *env)
{
	t_2dpair		z;
	t_2dpair		tmp;
	int			i;
	t_frac_gen	*gen;

	i = 0;
	z.x = 0;
	z.y = 0;
	gen = (t_frac_gen *)env->app.d;
	while ((z.x * z.x + z.y * z.y) <= 4 && i < gen->it)
	{
		tmp = z;
		z.x = (z.x * z.x) - (z.y * z.y) + point.x;
		z.y = 2 * tmp.x * z.y + point.y;
		i++;
	}
	if (i != gen->it)
		drawer_put_pixel(c, get_color(i / (double)gen->it), &env->rend);
}
