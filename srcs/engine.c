/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 14:00:35 by nboste            #+#    #+#             */
/*   Updated: 2016/12/25 09:13:18 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "libft.h"
#include "error.h"
#include "drawer.h"
#include "SDL2/SDL_thread.h"

void	engine_init(t_env *env, void (*init)(t_env *), int (*process)(void *), void (*destroy)(t_env *))
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		ft_exit(MSG_SDL_INIT_FAILED);
	if (!(env->win.win_sdl = SDL_CreateWindow(env->win.name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, env->win.size.x, env->win.size.y, SDL_WINDOW_SHOWN)))
		ft_exit(MSG_SDL_INIT_FAILED);
	drawer_init(env);
	env->app.init = init;
	env->app.process = process;
	env->app.destroy = destroy;
	env->app.init(env);
}

int		engine_run(t_env *env)
{
	int	time;
	int	etime;

	event_reset(&env->event);
	etime = 0;
	time = SDL_GetTicks();
	env->thread = SDL_CreateThread(env->app.process, "Child", env);
	while (!env->event.exit)
	{
		etime = SDL_GetTicks() - time;
		if (etime < 1000 / FPS)
			SDL_Delay((1000 / FPS) - etime);
		time = SDL_GetTicks();
		event_process(&env->event);
		drawer_process(&env->rend);
	}
	SDL_WaitThread(env->thread, &time);
	engine_destroy(env);
	return (0);
}

void	engine_destroy(t_env *env)
{
	if (env->app.destroy)
		env->app.destroy(env);
	drawer_destroy(&env->rend);
	SDL_DestroyWindow(env->win.win_sdl);
	SDL_Quit();
}
