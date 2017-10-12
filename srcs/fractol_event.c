/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_event.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 14:02:17 by nboste            #+#    #+#             */
/*   Updated: 2017/10/12 12:15:27 by nboste           ###   ########.fr       */
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
	t_2dpair	pos;
	t_2dpair	l;

	l.x = fabs(f->max.x - f->min.x) * 1000;
	l.y = fabs(f->max.y - f->min.y) * 1000;
	if (ev->mouse.wup || ev->keys[SDL_SCANCODE_PAGEUP] ||
		ev->mouse.wdown || ev->keys[SDL_SCANCODE_PAGEDOWN])
	{
		s = 1.3;
		if (ev->mouse.wup || ev->keys[SDL_SCANCODE_PAGEUP])
			s = .7;
		pos.x = (ev->mouse.pos.x / (double)env->rend.size.x);
		pos.y = (ev->mouse.pos.y / (double)env->rend.size.y);
		f->max.x = l.x * pos.x / 1000 + f->min.x + (l.x / 2000. * s);
		f->min.x = l.x * pos.x / 1000 + f->min.x - (l.x / 2000. * s);
		f->max.y = l.y * pos.y / 1000 + f->min.y + (l.y / 2000. * s);
		f->min.y = l.y * pos.y / 1000 + f->min.y - (l.y / 2000. * s);
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
	t_2dpair	diff;

	diff.x = f->max.x - f->min.x;
	diff.y = f->max.y - f->min.y;
	if (ev->keys[SDL_SCANCODE_W])
	{
		f->max.y -= 0.1 * diff.y;
		f->min.y -= 0.1 * diff.y;
	}
	if (ev->keys[SDL_SCANCODE_A])
	{
		f->max.x -= 0.1 * diff.x;
		f->min.x -= 0.1 * diff.x;
	}
	if (ev->keys[SDL_SCANCODE_S])
	{
		f->max.y += 0.1 * diff.y;
		f->min.y += 0.1 * diff.y;
	}
	if (ev->keys[SDL_SCANCODE_D])
	{
		f->max.x += 0.1 * diff.x;
		f->min.x += 0.1 * diff.x;
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
	if (ev->keys[SDL_SCANCODE_W] || ev->keys[SDL_SCANCODE_A]
			|| ev->keys[SDL_SCANCODE_S] || ev->keys[SDL_SCANCODE_D])
		f->draw = 1;
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
