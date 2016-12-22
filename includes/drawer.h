/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 06:01:47 by nboste            #+#    #+#             */
/*   Updated: 2016/12/22 13:50:57 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAWER_H
# define DRAWER_H

# include "types.h"
# include <math.h>

void	drawer_init(t_env *env);

void	drawer_process(t_renderer *rend);

void	drawer_destroy(t_renderer *rend);

void	drawer_put_pixel(t_2ipair coord, uint32 color, t_renderer *rend);

void	drawer_clean(t_renderer *rend);

void	drawer_wait_copy(t_env *env);

#endif
