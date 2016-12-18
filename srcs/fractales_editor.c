/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractales_editor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 08:47:29 by nboste            #+#    #+#             */
/*   Updated: 2016/12/18 10:18:09 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractales_editor.h"
#include "fractales_generator.h"
#include "libft.h"

static void	process_more(t_event *event, t_env *env)
{
	t_pair	step;
	t_frac_gen *gen;

	gen = &env->gen;
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
	if (event->switch_mandelbrot)
	{
		init_mandelbrot(&env->gen);
		env->gen.current = mandelbrot;
	}
	if (event->switch_julia)
	{
		init_julia(&env->gen);
		env->gen.current = julia;
	}

}

void	process_event(t_event *event, t_env *env)
{
	t_pair	step;
	t_frac_gen *gen;

	gen = &env->gen;
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
