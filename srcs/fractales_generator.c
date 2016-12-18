/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractales_generator.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 07:06:55 by nboste            #+#    #+#             */
/*   Updated: 2016/12/18 11:03:47 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractales_generator.h"
#include "drawer.h"

static double	map(int x, int minx, int maxx, double nminx, double nmaxx)
{
	return ((x / (double)(maxx - minx)) * (nmaxx - nminx));
}

static uint32	get_color(double ratio)
{
	return ((int)(0xFF * ratio) << 8);
}

void	init_gen(t_frac_gen *gen)
{
	gen->current = mandelbrot;
	init_mandelbrot(gen);
}

void	process_gen(t_env *env)
{
	t_2ipair	c;
	t_pair		point;

	c.x = 0;
	while (c.x < env->rend.size.x)
	{
		c.y = 0;
		while (c.y < env->rend.size.y)
		{
			point.x = map(c.x, 0, env->rend.size.x, env->gen.min.x, env->gen.max.x) + env->gen.min.x;
			point.y = map(c.y, 0, env->rend.size.y, env->gen.min.y, env->gen.max.y) + env->gen.min.y;
			if (env->gen.current == mandelbrot)
				process_mandelbrot(c, point, env);
			else if (env->gen.current == julia)
				process_julia(c, point, env);
			c.y++;
		}
		c.x++;
	}
}

void	init_mandelbrot(t_frac_gen *gen)
{
	gen->max.x = 0.6;
	gen->max.y = 1.2;
	gen->min.x = -2.1;
	gen->min.y = -1.2;
	gen->it = 200;
	gen->base_it = 200;
}

void	process_mandelbrot(t_2ipair c, t_pair point, t_env *env)
{
	t_pair		z;
	t_pair		tmp;
	int			i;

	i = 0;
	z.x = 0;
	z.y = 0;
	while ((z.x * z.x + z.y * z.y) <= 4 && i < env->gen.it)
	{
		tmp = z;
		z.x = (z.x * z.x) - (z.y * z.y) + point.x;
		z.y = 2 * tmp.x * z.y + point.y;
		i++;
	}
	if (i != env->gen.it)
		drawer_put_pixel(c, get_color(i / (double)env->gen.it), &env->rend);
}

void	init_julia(t_frac_gen *gen)
{
	gen->max.x = 1;
	gen->max.y = 1.2;
	gen->min.x = -1;
	gen->min.y = -1.2;
	gen->it = 200;
	gen->base_it = 200;
}

void	process_julia(t_2ipair c, t_pair point, t_env *env)
{
	t_pair		z;
	t_pair		tmp;
	int			i;

	i = 0;
	z.x = point.x;
	z.y = point.y;
	point.x = 0.285;
	point.y = 0.01;
	while ((z.x * z.x + z.y * z.y) <= 4 && i < env->gen.it)
	{
		tmp = z;
		z.x = (z.x * z.x) - (z.y * z.y) + point.x;
		z.y = 2 * tmp.x * z.y + point.y;
		i++;
	}
	if (i == env->gen.it)
		drawer_put_pixel(c, 0xFF00, &env->rend);
}
