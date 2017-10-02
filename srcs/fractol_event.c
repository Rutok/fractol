/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_event.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 14:02:17 by nboste            #+#    #+#             */
/*   Updated: 2017/09/27 21:40:19 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_gen.h"
#include "fractol_event.h"
#include "libft.h"
#include "burning.h"
#include "julia.h"
#include "mandelbrot.h"
#include "vertex_utility.h"

void	process_fractol_event(t_env *env)
{
	t_event		*ev;
	t_frac_gen	*f;
	t_camera	*cam;

	ev = &env->event;
	f = (t_frac_gen *)env->app.d;
	cam = &f->scene.camera;
	if (ev->keys[SDL_SCANCODE_ESCAPE])
	{
		ev->exit = 1;
		return;
	}
	if (ev->mouse.move)
	{
		f->xratio = ev->mouse.pos.x / (double)env->win.size.x;
		f->draw = 1;
	}
	if (ev->keys[SDL_SCANCODE_W])
	{
		f->max.y += 0.1 * (f->max.y - f->min.y);
		f->min.y += 0.1 * (f->max.y - f->min.y);
		f->draw = 1;
	}
	if (ev->keys[SDL_SCANCODE_A])
	{
		f->max.x -= 0.1 * (f->max.x - f->min.x);
		f->min.x -= 0.1 * (f->max.x - f->min.x);
		f->draw = 1;
	}
	if (ev->keys[SDL_SCANCODE_S])
	{
		f->max.y -= 0.1 * (f->max.y - f->min.y);
		f->min.y -= 0.1 * (f->max.y - f->min.y);
		f->draw = 1;
	}
	if (ev->keys[SDL_SCANCODE_D])
	{
		f->max.x += 0.1 * (f->max.x - f->min.x);
		f->min.x += 0.1 * (f->max.x - f->min.x);
		f->draw = 1;
	}
	if (ev->keys[SDL_SCANCODE_PAGEUP])
	{
		f->max.x -= .1 * fabs(f->max.x - f->min.x);
		f->max.y -= .1 * fabs(f->max.y - f->min.y);
		f->min.x += .1 * fabs(f->max.x - f->min.x);
		f->min.y += .1 * fabs(f->max.y - f->min.y);
		f->draw = 1;
	}
	if (ev->keys[SDL_SCANCODE_PAGEDOWN])
	{
		f->max.x += .1 * fabs(f->max.x - f->min.x);
		f->max.y += .1 * fabs(f->max.y - f->min.y);
		f->min.x -= .1 * fabs(f->max.x - f->min.x);
		f->min.y -= .1 * fabs(f->max.y - f->min.y);
		f->draw = 1;
	}
	static int tmp_m;
	if (ev->keys[SDL_SCANCODE_M])
	{
		tmp_m = 1;
	}
	else if (tmp_m == 1)
	{
		if (cam->projection == parallel)
			cam->projection = perspective;
		else
			cam->projection = parallel;
		f->draw = 1;
		tmp_m = 0;
	}
	if (ev->keys[SDL_SCANCODE_I])
	{
		cam->speed *= 1.1;
	}
	if (ev->keys[SDL_SCANCODE_K])
	{
		cam->speed *= .9;
	}
	if (ev->keys[SDL_SCANCODE_U])
	{
		f->offset += 100;
		f->draw = 1;
	}
	if (ev->keys[SDL_SCANCODE_J])
	{
		f->offset -= 100;
		f->draw = 1;
	}
	if (ev->keys[SDL_SCANCODE_F1])
	{
		init_mandelbrot(f);
		f->draw = 1;
	}
	if (ev->keys[SDL_SCANCODE_F2])
	{
		init_julia(f);
		f->draw = 1;
	}
	if (ev->keys[SDL_SCANCODE_F3])
	{
		init_burning(f);
		f->draw = 1;
	}
	if (ev->keys[SDL_SCANCODE_Y])
	{
		f->it += 100;
		f->draw = 1;
	}
	if (ev->keys[SDL_SCANCODE_H])
	{
		f->it -= 100;
		f->draw = 1;
	}

}
