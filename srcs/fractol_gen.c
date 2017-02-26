/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_gen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 14:02:35 by nboste            #+#    #+#             */
/*   Updated: 2017/02/27 00:40:15 by nboste           ###   ########.fr       */
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

void	init_app(t_env *env)
{
	t_frac_gen	*gen;
	t_camera	*cam;

	if (!(env->app.d = malloc(sizeof(t_frac_gen))))
		ft_exit(MSG_MALLOC);
	gen = (t_frac_gen *)env->app.d;
	init_mandelbrot(gen);
	cam = &gen->scene.camera;
	init_camera(env, ft_degtorad(135), &gen->scene.camera);
	cam->pos.x = 0;
	cam->pos.y = 0;
	cam->pos.z = 10;
	cam->n.x = 0;
	cam->n.y = 0;
	cam->n.z = -1;
	cam->v.x = 1;
	cam->v.y = 0;
	cam->v.z = 0;
	cam->u.x = 0;
	cam->u.y = 1;
	cam->u.z = 0;
	cam->projection = parallel;
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

	color.r = 0;
	color.g = 0;
	color.b = 0;
	color.a = 0;
	gen = (t_frac_gen *)env->app.d;
	cam = &gen->scene.camera;
	i.y = 0;
	while (i.y < cam->size.y)
	{
		i.x = 0;
		while (i.x < cam->size.x)
		{
			p.x = (i.x / cam->size.x) * (gen->max.x - gen->min.x) + gen->min.x;
			p.y = (i.y / cam->size.y) * (gen->max.y - gen->min.y) + gen->min.y;
			if (gen->current == mandelbrot)
				process_mandelbrot(&p, gen);
			color.r = 0;
			if (p.z < gen->it)
				color.r = 255 * (p.z / gen->it);
			to_camera_space(&p, &c_s, cam);
			camera_project_vertex(&c_s, &c, cam);
			cam->pixels[i.y][i.x].color = color;
			i.x++;
		}
		i.y++;
	}
	return (1);
}
