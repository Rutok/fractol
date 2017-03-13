/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_gen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 14:02:35 by nboste            #+#    #+#             */
/*   Updated: 2017/03/10 16:32:33 by nboste           ###   ########.fr       */
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
#include "camera_drawer.h"
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
	gen->offset = -700;
}

static t_color get_color(double z)
{
	t_color c;
	t_color hsl;
	unsigned char region, reminder, p, q, t;

	hsl.r = round(120 * z);
	hsl.g = 100;
	hsl.b = 100;
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
	z *= 100;
	c.r = (unsigned char)(sin(0.016 * z + 4) * 230 + 25);
	c.g = (unsigned char)(sin(0.013 * z + 2) * 230 + 25);
	c.b = (unsigned char)(sin(0.01 * z + 1) * 230 + 25);
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
	t_point				p1;
	t_2dpair			zminmax;

	gen = (t_frac_gen *)env->app.d;
	process_fractol_event(env);
	if (gen->draw)
	{
		printf("maxx: %f minx: %f maxy: %f miny: %f\n", gen->max.x, gen->min.x, gen->max.y, gen->min.y);
		gen->draw = 0;
		color.r = 0;
		color.g = 10;
		color.b = 10;
		color.a = 0;
		cam = &gen->scene.camera;
		zminmax.y = 999999999;
		zminmax.x = -999999999;
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
				if (p.z != -gen->it)
				{
					if(zminmax.x < p.z)
						zminmax.x = p.z;
					if(zminmax.y > p.z)
						zminmax.y = p.z;
				}
				i.x++;
			}
			i.y++;
		}

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
				color.r = 0;
				if (p.z != -gen->it)
				{
					//	p.z *= 100;
					p.x = ((i.x) / (double)(cam->size.x + gen->offset)) * cam->size.x - (cam->size.x / 2);
					p.y = ((i.y) / (double)(cam->size.y + (gen->offset / cam->ratio))) * cam->size.y - (cam->size.y / 2);
					to_camera_space(&p, &c_s, cam);
					if (c_s.z > 0)
					{
						d = (p.x * p.x) + (p.y * p.y) + (p.z * p.z);
						color = get_color((p.z - zminmax.y) / (zminmax.x - zminmax.y));
						camera_project_vertex(&c_s, &c, cam);
						//	c.x = ((c.x) / (cam->size.x - 1 )) * (cam->size.x - 1);
						//	c.y = ((c.y) / (cam->size.y - 1)) * (cam->size.y - 1);
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
