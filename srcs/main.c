/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 12:37:05 by nboste            #+#    #+#             */
/*   Updated: 2016/12/21 06:23:52 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "fractol_gen.h"

int		main(int argc, char **argv)
{
	t_env	env;

	env.app.argc = argc;
	env.app.argv = argv;
	env.win.name = ft_strdup("Fract'ol");
	env.win.size.x = 1280;
	env.win.size.y = 720;
	engine_init(&env, &init_gen, &process_gen, NULL);
	return (engine_run(&env));
}
