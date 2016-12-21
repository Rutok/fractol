/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_gen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 14:02:35 by nboste            #+#    #+#             */
/*   Updated: 2016/12/21 07:45:23 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_gen.h"
#include "fractol_event.h"
#include "drawer.h"
#include "error.h"
#include "mandelbrot.h"
#include "julia.h"

/*static double	map(int x, int minx, int maxx, double nminx, double nmaxx)
{
	return ((x / (double)(maxx - minx)) * (nmaxx - nminx) + nminx);
}*/

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
	static t_frac_gen	prev;
	t_2ipair			c;
	t_2dpair			point;
	t_frac_gen			*gen;
	t_2dpair			f;

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
				f.x = gen->camera.pos.x - gen->camera.org.x;
				f.y = gen->camera.pos.y - gen->camera.org.y;
				point.x = (c.x / gen->camera.zoom) + f.x - ((env->rend.size.x / 2) / gen->camera.zoom);
				point.y = (c.y / gen->camera.zoom) + f.y - ((env->rend.size.y / 2) / gen->camera.zoom);
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
