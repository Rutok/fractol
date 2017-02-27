/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_event.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 14:02:17 by nboste            #+#    #+#             */
/*   Updated: 2017/02/27 04:58:29 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_gen.h"
#include "fractol_event.h"
#include "libft.h"
#include "mandelbrot.h"
#include "julia.h"
#include "buddhabrot.h"
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
		//f->draw = 1;
	}
	/*static		t_2dpair off;
	  if (ev->mouse.move)
	  {
	  t_2dpair	d;
	  t_3dvertex	z;
	  z.x = 0;
	  z.y = 0;
	  z.z = 1;
	  d.x = ev->mouse.pos.x + off.x - (cam->size.x / 2);
	  d.y = ev->mouse.pos.y + off.y - (cam->size.y / 2);
	  off.x = d.x;
	  off.y = d.y;
	  if (d.x != 0 && d.y != 0)
	  {
	  d.x *= -cam->sensitivity;
	  d.y *= -0.1;
	  off.x /= 10;
	  off.y /= 10;
	  rotate_3dvertex(&cam->u, z, ft_degtorad(d.x));
	  rotate_3dvertex(&cam->n, z, ft_degtorad(d.x));
	  rotate_3dvertex(&cam->v, z, ft_degtorad(d.x));
	  rotate_3dvertex(&cam->n, cam->u, ft_degtorad(d.y));
	  rotate_3dvertex(&cam->v, cam->u, ft_degtorad(d.y));
	  SDL_WarpMouseInWindow(NULL, cam->size.x / 2, cam->size.y / 2);
	  f->draw = 1;
	  }
	  }*/
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
		f->max.y += 0.1 * (f->max.y - f->min.y);
		f->min.y += 0.1 * (f->max.y - f->min.y);
		f->draw = 1;
	}
	if (ev->keys[SDL_SCANCODE_PAGEUP])
	{
		f->max.x *= .9;
		f->max.y *= .9;
		f->min.x *= .9;
		f->min.y *= .9;
		f->draw = 1;
	}
	if (ev->keys[SDL_SCANCODE_PAGEDOWN])
	{
		f->max.x *= 1.1;
		f->max.y *= 1.1;
		f->min.x *= 1.1;
		f->min.y *= 1.1;
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
}
