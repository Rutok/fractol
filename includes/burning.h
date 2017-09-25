/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 15:16:19 by nboste            #+#    #+#             */
/*   Updated: 2017/09/25 15:16:51 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BURNING_H
# define BURNING_H

# include "fractol_gen.h"

void	init_burning(t_frac_gen *gen);

void	process_burning(t_3dvertex *point, t_frac_gen *gen);

#endif
