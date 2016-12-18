/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 03:54:07 by nboste            #+#    #+#             */
/*   Updated: 2016/12/18 09:50:23 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"
#include "error.h"
#include "drawer.h"
#include "fractales_generator.h"
#include "fractales_editor.h"

void	fractol_init(t_env *env)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		ft_exit(MSG_SDL_INIT_FAILED);
	if (!(env->win.win_sdl = SDL_CreateWindow(WIN_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN)))
		ft_exit(MSG_SDL_INIT_FAILED);
	env->win.size.x = WIN_WIDTH;
	env->win.size.y = WIN_HEIGHT;
	drawer_init(env);
}

int		fractol_run(t_env *env)
{
	event_reset(&env->event);
	init_gen(&env->gen);
	while (!env->event.exit)
	{
		drawer_clean(&env->rend);
		process_gen(env);
		event_process(&env->event);
		process_event(&env->event, env);
		drawer_process(&env->rend);
	}
	fractol_destroy(env);
	return (0);
}

void	fractol_destroy(t_env *env)
{
	drawer_destroy(&env->rend);
	SDL_DestroyWindow(env->win.win_sdl);
	SDL_Quit();
}

int		main(void)
{
	t_env	env;

	fractol_init(&env);
	return (fractol_run(&env));
}
