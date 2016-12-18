/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractales_generator.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 07:07:06 by nboste            #+#    #+#             */
/*   Updated: 2016/12/18 09:54:58 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTALES_GENERATOR_H
# define FRACTALES_GENERATOR_H

# include "types.h"

void	init_gen(t_frac_gen *gen);

void	process_gen(t_env *env);

void	init_mandelbrot(t_frac_gen *gen);

void	process_mandelbrot(t_2ipair c, t_pair point, t_env *env);

void	init_julia(t_frac_gen *gen);

void	process_julia(t_2ipair c, t_pair point, t_env *env);

#endif
