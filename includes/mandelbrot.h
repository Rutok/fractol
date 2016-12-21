/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 17:51:50 by nboste            #+#    #+#             */
/*   Updated: 2016/12/20 17:53:15 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANDELBROT_H
# define MANDELBROT_H

# include "fractol_gen.h"

void	init_mandelbrot(t_frac_gen *gen);

void	process_mandelbrot(t_2ipair c, t_2dpair point, t_env *env);

#endif
