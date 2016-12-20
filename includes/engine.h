/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 14:00:13 by nboste            #+#    #+#             */
/*   Updated: 2016/12/20 14:00:20 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "types.h"
# include "event.h"

# define FPS 60

/*
 * Init SDL modules, and create data structures
*/
void	engine_init(t_env *env, void (*init)(t_env *), void (*process)(t_env *), void (*destroy)(t_env *));

/*
 * Run the actual program
*/
int		engine_run(t_env *env);

/*
 * Kill everything
*/
void	engine_destroy(t_env *env);

#endif
