/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_gen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 14:02:35 by nboste            #+#    #+#             */
/*   Updated: 2017/10/11 15:58:33 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_gen.h"
#include "fractol_event.h"
#include "drawer.h"
#include "error.h"
#include "mandelbrot.h"
#include "julia.h"
#include "burning.h"
#include "camera.h"
#include "camera_drawer.h"
#include <stdio.h>

static void		init_cam(t_env *env)
{
	t_camera	*cam;
	t_frac_gen	*gen;

	if (!(env->app.d = malloc(sizeof(t_frac_gen))))
		ft_exit(MSG_MALLOC);
	gen = (t_frac_gen *)env->app.d;
	cam = &gen->scene.camera;
	init_camera(env, ft_degtorad(135), &gen->scene.camera);
	cam->pos.x = 0;
	cam->pos.y = 0;
	cam->pos.z = 210;
	cam->n.x = 0;
	cam->n.y = 0;
	cam->n.z = -1;
	cam->v.x = 0;
	cam->v.y = 1;
	cam->v.z = 0;
	cam->u.x = 1;
	cam->u.y = 0;
	cam->u.z = 0;
	cam->projection = parallel;
	cam->speed = 50;
	cam->sensitivity = 0.04;
	gen->draw = 1;
	gen->offset = -700;
}

void			init_app(t_env *env)
{
	t_frac_gen	*gen;

	init_cam(env);
	gen = (t_frac_gen *)env->app.d;
	if (env->app.argc != 2)
		ft_exit(USAGE);
	if (!ft_strcmp(env->app.argv[1], "mandelbrot"))
	{
		gen->current = mandelbrot;
		init_mandelbrot(gen);
	}
	else if (!ft_strcmp(env->app.argv[1], "julia"))
	{
		gen->current = julia;
		init_julia(gen);
	}
	else if (!ft_strcmp(env->app.argv[1], "burning"))
	{
		gen->current = burning;
		init_burning(gen);
	}
	else
		ft_exit(USAGE);
}

static void		process_point(t_3dvertex *p, t_frac_gen *gen)
{
	if (gen->current == mandelbrot)
		process_mandelbrot(p, gen);
	if (gen->current == julia)
		process_julia(p, gen);
	if (gen->current == burning)
		process_burning(p, gen);
}

static void		p_more(t_procp p, t_camera *cam, t_frac_gen *gen, t_env *env)
{
	p.p.x = (p.i.x / (double)((cam->size.x - 1) + gen->offset))
		* (gen->max.x - gen->min.x) + gen->min.x;
	p.p.y = ((cam->size.y - 1 + (gen->offset / cam->ratio) - p.i.y)
			/ (double)(cam->size.y - 1 + (gen->offset / cam->ratio)))
		* (gen->max.y - gen->min.y) + gen->min.y;
	p.p.z = 0;
	process_point(&p.p, gen);
	p.p.x = ((p.i.x) / (double)(cam->size.x + gen->offset))
		* cam->size.x - (cam->size.x / 2);
	p.p.y = ((p.i.y) / (double)(cam->size.y + (gen->offset / cam->ratio)))
		* cam->size.y - (cam->size.y / 2);
	to_camera_space(&p.p, &p.c_s, cam);
	if (p.p.z != -gen->it && p.c_s.z > 0)
	{
		p.d = (p.p.x * p.p.x) + (p.p.y * p.p.y) + (p.p.z * p.p.z);
		p.color = get_color(p.p.z);
		camera_project_vertex(&p.c_s, &p.c, cam);
		p.p1.pos.x = (int)(p.c.x);
		p.p1.pos.y = (int)(p.c.y);
		p.p1.z = p.d;
		p.p1.c = p.color;
		camera_draw_point(&p.p1, cam, env);
	}
}

int				process_app(void *venv)
{
	t_env		*env;
	t_frac_gen	*gen;
	t_camera	*cam;
	t_procp		p;

	env = (t_env *)venv;
	gen = (t_frac_gen *)env->app.d;
	cam = &gen->scene.camera;
	process_fractol_event(env);
	if (gen->draw)
	{
		gen->draw = 0;
		p.i.y = 0;
		while (p.i.y < cam->size.y + (gen->offset / cam->ratio))
		{
			p.i.x = -1;
			while (++p.i.x < cam->size.x + (gen->offset))
			{
				p_more(p, cam, gen, env);
			}
			p.i.y++;
		}
		drawer_wait_copy(env, cam);
	}
	return (1);
}
