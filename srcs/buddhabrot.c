/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buddhabrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/23 00:56:07 by nboste            #+#    #+#             */
/*   Updated: 2017/01/07 22:55:53 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buddhabrot.h"
#include "drawer.h"

/*static uint32	get_color(double ratio)
{
	return ((int)(0xFF * ratio) << 8);
}
*/
void	init_buddhabrot(t_frac_gen *gen)
{
	gen->max.x = 0.6;
	gen->max.y = 1.2;
	gen->min.x = -2.1;
	gen->min.y = -1.2;
	gen->camera.pos.x = (gen->max.x - gen->min.x) / 2;
	gen->camera.org.x = (gen->max.x - gen->min.x) / 2;
	gen->camera.pos.y = (gen->max.y - gen->min.y) / 2;
	gen->camera.org.y = (gen->max.y - gen->min.y) / 2;
	gen->camera.zoom = 600;
	gen->it = 20000;
	gen->base_it = 20000;
}

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

static void	buddha_draw(unsigned int *pixels, t_env * env)
{
	t_2ipair c;
	uint32	color;

	c.x = 0;
	while (c.x < env->rend.size.x)
	{
		c.y = 0;
		while (c.y < env->rend.size.y)
		{
			color = 0;
			color += MIN((int)(pixels[c.x + c.y * env->rend.size.x]) * 5, 255);
			color = color << 8;
			color += MIN((int)(pixels[c.x + c.y * env->rend.size.x]) * 5, 255);
			color = color << 8;
			color += MIN((int)(pixels[c.x + c.y * env->rend.size.x]) * 5, 255);
			color = color << 8;
			color += 0xFF;
			drawer_put_pixel(c, color, &env->rend);
			pixels[c.x + c.y * env->rend.size.x] = 0;
			c.y++;
		}
		c.x++;
	}
}

void	process_buddhabrot(t_2ipair c, t_2dpair point, t_env *env)
{
	t_2dpair		z;
	t_2dpair		tmp;
	int			i;
	t_frac_gen	*gen;
	static unsigned int *pixels;
	t_list			*points;

	points = NULL;
	if (!pixels)
		pixels = (unsigned int *)calloc(sizeof(unsigned int), env->rend.size.x * env->rend.size.y);
	i = 0;
	z.x = 0;
	z.y = 0;
	gen = (t_frac_gen *)env->app.d;
	while ((z.x * z.x + z.y * z.y) <= 4 && i < gen->it)
	{
		t_2dpair t;
		tmp = z;
		z.x = (z.x * z.x) - (z.y * z.y) + point.x;
		z.y = 2 * tmp.x * z.y + point.y;
		i++;
		t.x = -((z.x - gen->camera.pos.x + gen->camera.org.x) * gen->camera.zoom - (env->rend.size.x / 2));
		t.y = -((z.y - gen->camera.pos.y + gen->camera.org.y) * gen->camera.zoom - (env->rend.size.y / 2));
		ft_lstadd(&points, ft_lstnew((void *)&t, sizeof(t_2dpair)));
	}
	t_list *l;
	l = points;
	if (i != gen->it)
	{
		while (points)
		{
			t_2dpair *pt;
			pt = (t_2dpair *)points->content;
			if (pt->x < env->rend.size.x && pt->y < env->rend.size.y && round(pt->x) > 0 && round(pt->y) > 0)
				pixels[(int)(env->rend.size.x * (round(pt->y) - 1) + round(pt->x))]++;
			points = points->next;
		}
	}
	ft_lstdel(&l, ft_free);
	if (c.x == env->rend.size.x - 1 && c.y == env->rend.size.y - 1)
		buddha_draw(pixels, env);
}
