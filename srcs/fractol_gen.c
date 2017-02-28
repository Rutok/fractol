/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_gen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 14:02:35 by nboste            #+#    #+#             */
/*   Updated: 2017/02/28 01:05:39 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_gen.h"
#include "fractol_event.h"
#include "drawer.h"
#include "error.h"
#include "mandelbrot.h"
#include "julia.h"
#include "buddhabrot.h"
#include "camera.h"
#include <stdio.h>

void	init_app(t_env *env)
{
	t_frac_gen	*gen;
	t_camera	*cam;

	if (!(env->app.d = malloc(sizeof(t_frac_gen))))
		ft_exit(MSG_MALLOC);
	gen = (t_frac_gen *)env->app.d;
	gen->draw = 1;
	init_mandelbrot(gen);
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
}

static t_color get_color(double z)
{
	t_color c;

	c.a = 0;
	if (z < 20)
	{
		c.r = 0;
		c.g = (z / 20) * 255;
		c.b = 255;
	}
	else if (z < 60)
	{
		c.r = (z / 60) * 255;
		c.g = 255;
		c.b = 0;
	}
	else
	{
		c.r = 255;
		c.g = 0;
		c.b = (z / 200) * 255;
	}
	return (c);
}

int	process_app(void *venv)
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
	int					off;

	gen = (t_frac_gen *)env->app.d;
	process_fractol_event(env);
	off = 0;
	if (gen->draw)
	{
		printf("maxx: %f minx: %f maxy: %f miny: %f\n", gen->max.x, gen->min.x, gen->max.y, gen->min.y);
		gen->draw = 0;
		color.r = 0;
		color.g = 10;
		color.b = 10;
		color.a = 0;
		cam = &gen->scene.camera;
		if (cam->projection == perspective)
			off = 100000;
		i.y = 0;
		while (i.y < cam->size.y + off)
		{
			i.x = 0;
			while (i.x < cam->size.x + off)
			{
				p.x = (i.x / (double)(cam->size.x - 1)) * (gen->max.x - gen->min.x) + gen->min.x; p.y = ((cam->size.y - 1 - i.y) / (double)(cam->size.y - 1)) * (gen->max.y - gen->min.y) + gen->min.y;
				p.z = 0;
				if (gen->current == mandelbrot)
					process_mandelbrot(&p, gen);
				color.r = 0;
				if ((int)p.z < gen->it)
				{
					p.x = i.x - (cam->size.x / 2);
					p.y = i.y - (cam->size.y / 2);
					to_camera_space(&p, &c_s, cam);
					if (c_s.z > 0)
					{
						d = (p.x * p.x) + (p.y * p.y) + (p.z * p.z);
						color = get_color(p.z);
						camera_project_vertex(&c_s, &c, cam);
						c_s.z /= 20;
						if (c.y >= 0 && c.y < cam->size.y && c.x >= 0 && c.x < cam->size.x)
						{
							if (cam->pixels[(int)c.y][(int)c.x].z_buffer == -1 || cam->pixels[(int)c.y][(int)c.x].z_buffer > d)
							{
								cam->pixels[(int)c.y][(int)c.x].color = color;
								cam->pixels[(int)c.y][(int)c.x].z_buffer = d;
							}
						}
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
