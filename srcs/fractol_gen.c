/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_gen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 14:02:35 by nboste            #+#    #+#             */
/*   Updated: 2016/12/23 06:07:39 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_gen.h"
#include "fractol_event.h"
#include "drawer.h"
#include "error.h"
#include "mandelbrot.h"
#include "julia.h"
#include "buddhabrot.h"

/*static double	map(int x, int minx, int maxx, double nminx, double nmaxx)
  {
  return ((x / (double)(maxx - minx)) * (nmaxx - nminx) + nminx);
  }*/

static void	print_fps(void)
{
	static int time;
	static int fps;

	fps++;
	if (!time)
		time = SDL_GetTicks();
	if (SDL_GetTicks() >= (Uint32)time + 1000)
	{
		ft_putstr("FPS : ");
		ft_putnbr(fps);
		ft_putchar('\n');
		fps = 0;
		time = SDL_GetTicks();
	}
}

void	init_app(t_env *env)
{
	t_frac_gen	*gen;

	if (!(env->app.d = malloc(sizeof(t_frac_gen))))
		ft_exit(MSG_MALLOC);
	gen = (t_frac_gen *)env->app.d;
	gen->current = mandelbrot;
	init_mandelbrot(gen);
}

int	process_app(void *venv)
{
	t_env *env = (t_env *)venv;
	static t_frac_gen	prev;
	t_2ipair			c;
	t_2dpair			point;
	t_frac_gen			*gen;
	t_2dpair			f;

	while (!env->event.exit)
	{
		print_fps();
		process_gen_event(&env->event, env);
		gen = (t_frac_gen *)env->app.d;
		if (ft_memcmp(gen, &prev, sizeof(t_frac_gen)) && !env->event.exit)
		{
			env->event.draw = 1;
			drawer_clean(&env->rend);
			c.x = 0;
			while (c.x < env->rend.size.x)
			{
				c.y = 0;
				while (c.y < env->rend.size.y)
				{
					if (env->event.exit)
						return (1);
					f.x = gen->camera.pos.x - gen->camera.org.x;
					f.y = gen->camera.pos.y - gen->camera.org.y;
					point.x = (c.x / gen->camera.zoom) + f.x - ((env->rend.size.x / 2) / gen->camera.zoom);
					point.y = (c.y / gen->camera.zoom) + f.y - ((env->rend.size.y / 2) / gen->camera.zoom);
					if (gen->current == mandelbrot)
						process_mandelbrot(c, point, env);
					else if (gen->current == julia)
						process_julia(c, point, env);
					else if (gen->current == buddhabrot)
						process_buddhabrot(c, point, env);
					c.y++;
				}
				c.x++;
			}
			drawer_wait_copy(env);
		}
		prev = *gen;
	}
	return (1);
}
