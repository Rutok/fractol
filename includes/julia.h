/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 18:00:54 by nboste            #+#    #+#             */
/*   Updated: 2016/12/20 18:01:59 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JULIA_H
# define JULIA_H

# include "fractol_gen.h"

void	init_julia(t_frac_gen *gen);

void	process_julia(t_2ipair c, t_2dpair point, t_env *env);

#endif
