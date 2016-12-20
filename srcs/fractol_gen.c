/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_gen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 14:02:35 by nboste            #+#    #+#             */
/*   Updated: 2016/12/20 14:04:07 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_gen.h"
#include "fractol_event.h"
#include "drawer.h"
#include "error.h"

static double	map(int x, int minx, int maxx, double nminx, double nmaxx)
{
	return ((x / (double)(maxx - minx)) * (nmaxx - nminx));
}

static uint32	get_color(double ratio)
{
	return ((int)(0xFF * ratio) << 8);
}

void	init_gen(t_env *env)
{
	t_frac_gen	*gen;

	if (!(env->app.d = malloc(sizeof(t_frac_gen))))
		ft_exit(MSG_MALLOC);
	gen = (t_frac_gen *)env->app.d;
	gen->current = mandelbrot;
	init_mandelbrot(gen);
}

void	process_gen(t_env *env)
{
	static t_frac_gen prev;
	t_2ipair	c;
	t_pair		point;
	t_frac_gen	*gen;

	gen = (t_frac_gen *)env->app.d;
	c.x = 0;
	process_gen_event(&env->event, env);
	if (ft_memcmp(gen, &prev, sizeof(t_frac_gen)))
	{
		env->event.draw = 1;
		drawer_clean(&env->rend);
		while (c.x < env->rend.size.x)
		{
			c.y = 0;
			while (c.y < env->rend.size.y)
			{
				point.x = map(c.x, 0, env->rend.size.x, gen->min.x, gen->max.x) + gen->min.x;
				point.y = map(c.y, 0, env->rend.size.y, gen->min.y, gen->max.y) + gen->min.y;
				if (gen->current == mandelbrot)
					process_mandelbrot(c, point, env);
				else if (gen->current == julia)
					process_julia(c, point, env);
				c.y++;
			}
			c.x++;
		}
	}
	prev = *gen;
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
	t_frac_gen	*gen;

	i = 0;
	z.x = point.x;
	z.y = point.y;
	point.x = 0.285;
	point.y = 0.01;
	gen = (t_frac_gen *)env->app.d;
	while ((z.x * z.x + z.y * z.y) <= 4 && i < gen->it)
	{
		tmp = z;
		z.x = (z.x * z.x) - (z.y * z.y) + point.x;
		z.y = 2 * tmp.x * z.y + point.y;
		i++;
	}
	if (i == gen->it)
		drawer_put_pixel(c, 0xFF00, &env->rend);
}
