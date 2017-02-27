/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 12:37:05 by nboste            #+#    #+#             */
/*   Updated: 2017/02/27 07:36:52 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "fractol_gen.h"

int		main(int argc, char **argv)
{
	t_env	env;

	env.app.argc = argc;
	env.app.argv = argv;
	env.win.name = ft_strdup("fract'ol");
	env.win.size.x = 1920;
	env.win.size.y = 1080;
	engine_init(&env, &init_app, &process_app, NULL);
	return (engine_run(&env));
}
