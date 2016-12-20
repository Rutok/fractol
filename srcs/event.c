/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 05:15:18 by nboste            #+#    #+#             */
/*   Updated: 2016/12/20 13:08:57 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event.h"

void	event_process(t_event *event)
{
	SDL_Event	ev;

	event_reset(event);
	while (SDL_PollEvent(&ev))
	{
		if (ev.type == SDL_QUIT)
			event->exit = 1;
		else if (ev.type == SDL_KEYDOWN)
			event_handle_keyboard(&ev, event);
		else if (ev.type == SDL_MOUSEMOTION)
			event_handle_mouse(&ev, event);
	}
}

void	event_reset(t_event *event)
{
	event->exit = 0;
	event->move_right = 0;
	event->move_up = 0;
	event->move_down = 0;
	event->move_left = 0;
	event->plus = 0;
	event->minus = 0;
	event->mouse_move = 0;
	event->key_f1= 0;
	event->key_f2= 0;
	event->draw = 0;
}

void	event_handle_keyboard(SDL_Event *ev, t_event *event)
{
	SDL_Keycode	k;

	k = ev->key.keysym.sym;
	if (k == SDLK_ESCAPE)
		event->exit = 1;
	else if (k == SDLK_UP)
		event->move_up = 1;
	else if (k == SDLK_DOWN)
		event->move_down = 1;
	else if (k == SDLK_LEFT)
		event->move_left = 1;
	else if (k == SDLK_RIGHT)
		event->move_right = 1;
	else if (k == SDLK_EQUALS)
		event->plus = 1;
	else if (k == SDLK_MINUS)
		event->minus = 1;
	else if (k == SDLK_F1)
		event->key_f1= 1;
	else if (k == SDLK_F2)
		event->key_f2= 1;
}

void	event_handle_mouse(SDL_Event *ev, t_event *event)
{
	event->mouse_move = 1;
	event->mouse_pos.x = ev->motion.x;
	event->mouse_pos.y = ev->motion.y;
}
