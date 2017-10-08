/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_gen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 14:02:35 by nboste            #+#    #+#             */
/*   Updated: 2017/10/08 18:23:45 by nboste           ###   ########.fr       */
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

static t_color	get_color_more(t_color hsl, t_color c)
{
	unsigned char region, reminder, p, q, t;

	region = hsl.r / 43;
	reminder = (hsl.r - (region * 43)) * 6;
	p = (hsl.g * (255 - hsl.b)) >> 8;
	q = (hsl.g * (255 - ((hsl.b * reminder) >> 8))) >> 8;
	t = (hsl.g * (255 - ((hsl.g * (255 - reminder)) >> 8 ))) >> 8;
	switch (region)
	{
		case 0:
			c.r = hsl.b; c.g = t; c.b = p;
			break;
		case 1:
			c.r = q; c.g = hsl.b; c.b = p;
			break;
		case 2:
			c.r = p; c.g = hsl.b; c.b = t;
			break;
		case 3:
			c.r = p; c.g = q; c.b = hsl.b;
			break;
		case 4:
			c.r = t; c.g = p; c.b = hsl.b;
			break;
		default:
			c.r = hsl.b; c.g = p; c.b = q;
			break;
	}
	return (c);
}

static t_color	get_color(double z)
{
	t_color c;
	t_color hsl;

	hsl.r = 100 + round(fabs(z));
	hsl.g = 100;
	hsl.b = 100;
	c.r = 0;
//	return (hsl);
	return (get_color_more(hsl, c));
}

int				process_app(void *venv)
{
	t_env *env = (t_env *)venv;
	t_frac_gen			*gen;
	t_camera			*cam;
	t_3dvertex			p;
	t_3dvertex			c_s;
	t_2ipair			i;
	t_2dpair			c;
	t_color				color;
	double				d;
	t_point				p1;

	gen = (t_frac_gen *)env->app.d;
	process_fractol_event(env);
	if (gen->draw)
	{
		gen->draw = 0;
		cam = &gen->scene.camera;
		i.y = 0;
		while (i.y < cam->size.y + (gen->offset / cam->ratio))
		{
			i.x = 0;
			while (i.x < cam->size.x + (gen->offset))
			{
				p.x = (i.x / (double)((cam->size.x - 1) + gen->offset)) * (gen->max.x - gen->min.x) + gen->min.x;
				p.y = ((cam->size.y - 1 + (gen->offset / cam->ratio) - i.y) / (double)(cam->size.y - 1 + (gen->offset / cam->ratio))) * (gen->max.y - gen->min.y) + gen->min.y;
				p.z = 0;
				if (gen->current == mandelbrot)
					process_mandelbrot(&p, gen);
				if (gen->current == julia)
					process_julia(&p, gen);
				if (gen->current == burning)
					process_burning(&p, gen);
				if (p.z != -gen->it)
				{
					p.x = ((i.x) / (double)(cam->size.x + gen->offset)) * cam->size.x - (cam->size.x / 2);
					p.y = ((i.y) / (double)(cam->size.y + (gen->offset / cam->ratio))) * cam->size.y - (cam->size.y / 2);
					to_camera_space(&p, &c_s, cam);
					if (c_s.z > 0)
					{
						d = (p.x * p.x) + (p.y * p.y) + (p.z * p.z);
						color = get_color(p.z);
						camera_project_vertex(&c_s, &c, cam);
						p1.pos.x = (int)(c.x);
						p1.pos.y = (int)(c.y);
						p1.z = d;
						p1.c = color;
						camera_draw_point(&p1, cam, env);
					}
				}
				i.x++;
			}
			i.y++;
		}
		drawer_wait_copy(env, cam);
	}
	return (1);
}
