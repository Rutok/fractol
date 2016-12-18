/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 05:15:39 by nboste            #+#    #+#             */
/*   Updated: 2016/12/18 09:20:58 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_H
# define EVENT_H

# include "types.h"
# include "SDL2/SDL.h"

void	event_process(t_event *event);

void	event_reset(t_event *event);

void	event_handle_keyboard(SDL_Event *ev, t_event *event);

void	event_handle_mouse(SDL_Event *ev, t_event *event);

#endif
