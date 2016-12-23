/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_gen.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 14:01:25 by nboste            #+#    #+#             */
/*   Updated: 2016/12/23 00:54:44 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTALES_GENERATOR_H
# define FRACTALES_GENERATOR_H

# include "types.h"

typedef struct	s_camera
{
	t_3dvertex	pos;
	t_3dvertex	org;
	double		zoom;
}				t_camera;

typedef enum	e_fractales
{
	mandelbrot,
	julia,
	buddhabrot
}				t_fractales;

typedef struct	s_frac_gen
{
	t_2dpair	max;
	t_2dpair	min;
	int			it;
	int			base_it;
	t_fractales	current;
	t_camera	camera;;
}				t_frac_gen;

void	init_app(t_env *env);

int		process_app(void *env);

#endif
