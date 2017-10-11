/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_gen.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 14:01:25 by nboste            #+#    #+#             */
/*   Updated: 2017/10/11 15:58:58 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_GEN_H
# define FRACTOL_GEN_H

# include "types.h"

# define USAGE "./fractol [fractal name]\n[mandelbrot] [julia] [burning]"

typedef enum	e_fractales
{
	mandelbrot,
	julia,
	burning
}				t_fractales;

typedef struct	s_frac_gen
{
	t_2dpair	max;
	t_2dpair	min;
	int			it;
	int			base_it;
	t_fractales	current;
	t_scene		scene;
	t_bool		draw;
	int			offset;
	double		xratio;
}				t_frac_gen;

typedef struct	s_hsl
{
	unsigned char	region;
	unsigned char	reminder;
	unsigned char	p;
	unsigned char	q;
	unsigned char	t;
}				t_hsl;

typedef struct	s_procp
{
	t_3dvertex		p;
	t_3dvertex		c_s;
	t_2ipair		i;
	t_2dpair		c;
	t_color			color;
	double			d;
	t_point			p1;
}				t_procp;

void			init_app(t_env *env);

int				process_app(void *env);

t_color			get_color(double z);

t_color			hsl_more(t_hsl h, t_color c, t_color hsl);

#endif
