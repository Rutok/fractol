/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_gen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 14:02:35 by nboste            #+#    #+#             */
/*   Updated: 2016/12/20 18:03:06 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_gen.h"
#include "fractol_event.h"
#include "drawer.h"
#include "error.h"
#include "mandelbrot.h"
#include "julia.h"

static double	map(int x, int minx, int maxx, double nminx, double nmaxx)
{
	return ((x / (double)(maxx - minx)) * (nmaxx - nminx));
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
	t_2dpair		point;
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
