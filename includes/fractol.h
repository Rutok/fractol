/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 03:54:14 by nboste            #+#    #+#             */
/*   Updated: 2016/12/18 10:07:38 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "types.h"
# include "event.h"

# define WIN_NAME "Fractol"
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720

/*
 * Init SDL modules, and create data structures
*/
void	fractol_init(t_env *env);

/*
 * Run the actual program
*/
int		fractol_run(t_env *env);

/*
 * Kill everything
*/
void	fractol_destroy(t_env *env);

#endif

