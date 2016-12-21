/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_event.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 14:02:17 by nboste            #+#    #+#             */
/*   Updated: 2016/12/21 07:51:21 by nboste           ###   ########.fr       */
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
	step.x = (env->rend.size.x / gen->camera.zoom) * 0.1;
	step.y = (env->rend.size.y / gen->camera.zoom) * 0.1;
	if (event->plus)
	{
		gen->camera.zoom *= 1.2;
	}
	if (event->minus)
	{
		gen->camera.zoom *= 0.8;
	}
	if (event->mouse_move)
	{
		gen->it = event->mouse_pos.x * gen->base_it / env->rend.size.x;
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
	step.x = (env->rend.size.x / gen->camera.zoom) * 0.1;
	step.y = (env->rend.size.y / gen->camera.zoom) * 0.1;
	if (event->move_down)
	{
		gen->camera.pos.y += step.y;
	}
	if (event->move_up)
	{
		gen->camera.pos.y -= step.y;
	}
	if (event->move_left)
	{
		gen->camera.pos.x -= step.x;
	}
	if (event->move_right)
	{
		gen->camera.pos.x += step.x;
	}
	process_more(event, env);
}
