/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_event.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 14:02:17 by nboste            #+#    #+#             */
/*   Updated: 2017/10/08 18:00:33 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_gen.h"
#include "fractol_event.h"
#include "libft.h"
#include "burning.h"
#include "julia.h"
#include "mandelbrot.h"
#include "vertex_utility.h"

static void		process_mouse_event(t_event *ev, t_frac_gen *f, t_env *env)
{
	double		s;
	t_2dpair	center;
	t_2dpair	pos;

	if (ev->mouse.lclick || ev->keys[SDL_SCANCODE_PAGEUP] ||
		ev->mouse.rclick || ev->keys[SDL_SCANCODE_PAGEDOWN])
	{
		s = 1.3;
		if (ev->mouse.lclick || ev->keys[SDL_SCANCODE_PAGEUP])
			s = .7;
		pos.x = ev->mouse.pos.x / (double)env->rend.size.x;
		pos.y = ev->mouse.pos.y / (double)env->rend.size.y;
		center.x = fabs(f->max.x - f->min.x) * pos.x + f->min.x;
		center.y = fabs(f->max.y - f->min.y) * pos.y + f->min.y;
		f->max.x = center.x + (fabs(f->max.x - f->min.x) * s / 2);
		f->min.x = center.x - (fabs(f->max.x - f->min.x) * s / 2);
		f->max.y = center.y + (fabs(f->max.y - f->min.y) * s / 2);
		f->min.y = center.y - (fabs(f->max.y - f->min.y) * s / 2);
		f->draw = 1;
	}
	if (ev->mouse.move)
	{
		f->xratio = ev->mouse.pos.x / (double)env->win.size.x;
		f->draw = 1;
	}
}

static void		process_mvt_keys(t_event *ev, t_frac_gen *f)
{
	if (ev->keys[SDL_SCANCODE_W])
	{
		f->max.y -= 0.1 * (f->max.y - f->min.y);
		f->min.y -= 0.1 * (f->max.y - f->min.y);
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
		f->max.y += 0.1 * (f->max.y - f->min.y);
		f->min.y += 0.1 * (f->max.y - f->min.y);
		f->draw = 1;
	}
	if (ev->keys[SDL_SCANCODE_D])
	{
		f->max.x += 0.1 * (f->max.x - f->min.x);
		f->min.x += 0.1 * (f->max.x - f->min.x);
		f->draw = 1;
	}
}

static void		process_more_keys(t_event *ev, t_frac_gen *f)
{
	t_camera	*cam;

	cam = &f->scene.camera;
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
}

static void		process_more_again(t_event *ev, t_frac_gen *f)
{
	static int tmp_m;

	if (ev->keys[SDL_SCANCODE_M])
	{
		tmp_m = 1;
	}
	else if (tmp_m == 1)
	{
		if (f->scene.camera.projection == parallel)
			f->scene.camera.projection = perspective;
		else
			f->scene.camera.projection = parallel;
		f->draw = 1;
		tmp_m = 0;
	}
	if (ev->keys[SDL_SCANCODE_F1])
		init_mandelbrot(f);
	if (ev->keys[SDL_SCANCODE_F2])
		init_julia(f);
	if (ev->keys[SDL_SCANCODE_F3])
		init_burning(f);
	if (ev->keys[SDL_SCANCODE_F1] || ev->keys[SDL_SCANCODE_F2]
			|| ev->keys[SDL_SCANCODE_F3])
		f->draw = 1;
}

void			process_fractol_event(t_env *env)
{
	t_event		*ev;
	t_frac_gen	*f;

	ev = &env->event;
	f = (t_frac_gen *)env->app.d;
	if (ev->keys[SDL_SCANCODE_ESCAPE])
	{
		ev->exit = 1;
		return ;
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
	process_mouse_event(ev, f, env);
	process_mvt_keys(ev, f);
	process_more_keys(ev, f);
	process_more_again(ev, f);
}
