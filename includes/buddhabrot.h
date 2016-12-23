/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buddhabrot.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/23 00:57:10 by nboste            #+#    #+#             */
/*   Updated: 2016/12/23 01:01:42 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUDDHABROT_H
# define BUDDHABROT_H

# include "fractol_gen.h"

void	init_buddhabrot(t_frac_gen *gen);

void	process_buddhabrot(t_2ipair c, t_2dpair point, t_env *env);

#endif
