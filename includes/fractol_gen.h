/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_gen.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 14:01:25 by nboste            #+#    #+#             */
/*   Updated: 2016/12/20 14:01:29 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTALES_GENERATOR_H
# define FRACTALES_GENERATOR_H

# include "types.h"

typedef enum	e_fractales
{
	mandelbrot,
	julia
}				t_fractales;

typedef struct	s_frac_gen
{
	t_pair	max;
	t_pair	min;
	int		it;
	int		base_it;
	t_fractales current;
}				t_frac_gen;

void	init_gen(t_env *env);

void	process_gen(t_env *env);

void	init_mandelbrot(t_frac_gen *gen);

void	process_mandelbrot(t_2ipair c, t_pair point, t_env *env);

void	init_julia(t_frac_gen *gen);

void	process_julia(t_2ipair c, t_pair point, t_env *env);

#endif
