/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_event.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 14:02:17 by nboste            #+#    #+#             */
/*   Updated: 2016/12/20 18:05:50 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_gen.h"
#include "fractol_event.h"
#include "libft.h"
#include "mandelbrot.h"
#include "julia.h"

static void	process_more(t_event *event, t_env *env)
{
	t_2dpair	step;
	t_frac_gen *gen;

	gen = (t_frac_gen *)env->app.d;
	step.x = (gen->max.x - gen->min.x) * 0.1;
	step.y = (gen->max.y - gen->min.y) * 0.1;
	if (event->plus)
	{
		gen->max.x -= step.x;
		gen->max.y -= step.y;
		gen->min.x += step.x;
		gen->min.y += step.y;
	}
	if (event->minus)
	{
		gen->max.x += step.x;
		gen->max.y += step.y;
		gen->min.x -= step.x;
		gen->min.y -= step.y;
	}
	if (event->mouse_move)
	{
		gen->it = event->mouse_pos.x * gen->base_it / 1000;
	}
	if (event->key_f1)
	{
		init_mandelbrot(gen);
		gen->current = mandelbrot;
	}
	if (event->key_f2)
	{
		init_julia(gen);
		gen->current = julia;
	}

}

void	process_gen_event(t_event *event, t_env *env)
{
	t_2dpair	step;
	t_frac_gen *gen;

	gen = (t_frac_gen *)env->app.d;
	step.x = (gen->max.x - gen->min.x) * 0.1;
	step.y = (gen->max.y - gen->min.y) * 0.1;
	if (event->move_down)
	{
		gen->min.y += step.y;
		gen->max.y += step.y;
	}
	if (event->move_up)
	{
		gen->min.y -= step.y;
		gen->max.y -= step.y;
	}
	if (event->move_left)
	{
		gen->min.x -= step.x;
		gen->max.x -= step.x;
	}
	if (event->move_right)
	{
		gen->min.x += step.x;
		gen->max.x += step.x;
	}
	process_more(event, env);
}
