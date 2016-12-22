/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_event.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 14:02:17 by nboste            #+#    #+#             */
/*   Updated: 2016/12/22 14:38:04 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_gen.h"
#include "fractol_event.h"
#include "libft.h"
#include "mandelbrot.h"
#include "julia.h"

static void	process_more(t_event *event, t_env *env)
{
	t_frac_gen *gen;

	gen = (t_frac_gen *)env->app.d;
	if (event->mouse_move)
	{
		gen->it = event->mouse_pos.x * gen->base_it / env->rend.size.x;
		event->mouse_move = 0;
	}
	if (event->mouse_click)
	{
		gen->camera.pos.x += (event->mouse_pos.x / gen->camera.zoom) - ((env->rend.size.x / 2) / gen->camera.zoom);
		gen->camera.pos.y += (event->mouse_pos.y / gen->camera.zoom) - ((env->rend.size.y / 2) / gen->camera.zoom);
		gen->camera.zoom *= 1.2;
		event->mouse_click = 0;
	}
	if (event->key_f1)
	{
		init_mandelbrot(gen);
		gen->current = mandelbrot;
		event->key_f1 = 0;
	}
	if (event->key_f2)
	{
		init_julia(gen);
		gen->current = julia;
		event->key_f2 = 0;
	}

}

void	process_gen_event(t_event *event, t_env *env)
{
	t_2dpair	step;
	t_frac_gen *gen;

	gen = (t_frac_gen *)env->app.d;
	step.x = (env->rend.size.x / gen->camera.zoom) * 0.1;
	step.y = (env->rend.size.y / gen->camera.zoom) * 0.1;
	if (event->move_down)
	{
		gen->camera.pos.y += step.y;
		event->move_down = 0;
	}
	if (event->move_up)
	{
		gen->camera.pos.y -= step.y;
		event->move_up = 0;
	}
	if (event->move_left)
	{
		gen->camera.pos.x -= step.x;
		event->move_left = 0;
	}
	if (event->move_right)
	{
		gen->camera.pos.x += step.x;
		event->move_right = 0;
	}
	if (event->plus)
	{
		gen->camera.zoom *= 1.2;
		event->plus = 0;
	}
	if (event->minus)
	{
		event->minus = 0;
		gen->camera.zoom *= 0.8;
	}
	process_more(event, env);
}
