/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_event.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 14:02:17 by nboste            #+#    #+#             */
/*   Updated: 2017/01/17 04:34:35 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_gen.h"
#include "fractol_event.h"
#include "libft.h"
#include "mandelbrot.h"
#include "julia.h"
#include "buddhabrot.h"

static void	process_more(t_event *event, t_env *env)
{
	t_frac_gen *gen;

	gen = (t_frac_gen *)env->app.d;
	if (event->mouse.move)
	{
		gen->it = event->mouse.pos.x * gen->base_it / env->rend.size.x;
		event->mouse.move = 0;
	}
	if (event->mouse.lclick)
	{
		gen->camera.pos.x += (event->mouse.pos.x / gen->camera.zoom) - ((env->rend.size.x / 2) / gen->camera.zoom);
		gen->camera.pos.y += (event->mouse.pos.y / gen->camera.zoom) - ((env->rend.size.y / 2) / gen->camera.zoom);
		gen->camera.zoom *= 1.2;
		event->mouse.lclick = 0;
	}
	if (event->key_function.keys[KEY_F1])
	{
		init_mandelbrot(gen);
		gen->current = mandelbrot;
		event->key_function.keys[KEY_F1] = 0;
	}
	if (event->key_function.keys[KEY_F2])
	{
		init_julia(gen);
		gen->current = julia;
		event->key_function.keys[KEY_F2] = 0;
	}
	if (event->key_function.keys[KEY_F3])
	{
		init_buddhabrot(gen);
		gen->current = buddhabrot;
		event->key_function.keys[KEY_F3] = 0;
	}
}

void	process_gen_event(t_event *event, t_env *env)
{
	t_2dpair	step;
	t_frac_gen *gen;

	gen = (t_frac_gen *)env->app.d;
	step.x = (env->rend.size.x / gen->camera.zoom) * 0.1;
	step.y = (env->rend.size.y / gen->camera.zoom) * 0.1;
	if (event->key_special.keys[KEY_ESCAPE])
		event->exit = 1;
	if (event->key_nav.keys[KEY_DOWN])
	{
		gen->camera.pos.y += step.y;
		event->key_nav.keys[KEY_DOWN] = 0;
	}
	if (event->key_nav.keys[KEY_UP])
	{
		gen->camera.pos.y -= step.y;
		event->key_nav.keys[KEY_UP] = 0;
	}
	if (event->key_nav.keys[KEY_LEFT])
	{
		gen->camera.pos.x -= step.x;
		event->key_nav.keys[KEY_LEFT] = 0;
	}
	if (event->key_nav.keys[KEY_RIGHT])
	{
		gen->camera.pos.x += step.x;
		event->key_nav.keys[KEY_RIGHT] = 0;
	}
	if (event->key_nav.keys[KEY_PAGEUP])
	{
		gen->camera.zoom *= 1.2;
		event->key_nav.keys[KEY_PAGEUP] = 0;
	}
	if (event->key_nav.keys[KEY_PAGEDOWN])
	{
		gen->camera.zoom *= 0.8;
		event->key_nav.keys[KEY_PAGEDOWN] = 0;
	}
	process_more(event, env);
}
