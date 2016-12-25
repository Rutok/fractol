/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 04:36:59 by nboste            #+#    #+#             */
/*   Updated: 2016/12/25 09:07:03 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <SDL2/SDL.h>
# include "libft.h"

typedef struct	s_win
{
	SDL_Window	*win_sdl;
	t_2ipair	size;
	char		*name;
	t_bool		focus;
}				t_win;

typedef struct	s_renderer
{
	SDL_Renderer	*rend_sdl;
	SDL_Texture		*texture_sdl;
	uint32			*pixels;
	uint32			*pixels2;
	t_2ipair		size;
	t_bool			ready;
	t_bool			draw;
}				t_renderer;

typedef struct	s_event
{
	t_bool		exit;
	t_bool		focus;
	t_bool		move_left;
	t_bool		move_right;
	t_bool		move_up;
	t_bool		move_down;
	t_bool		plus;
	t_bool		minus;
	t_bool		mouse_move;
	t_bool		mouse_click;
	t_2ipair	mouse_pos;
	t_bool		key_f1;
	t_bool		key_f2;
	t_bool		key_f3;
	t_bool		draw;
}				t_event;

typedef struct s_env t_env;

typedef struct	s_app
{
	void	(*init)(t_env *);
	int	(*process)(void *);
	void	(*destroy)(t_env *);
	void	*d;
	int		argc;
	char	**argv;
}				t_app;

typedef struct s_env
{
	t_win	win;
	t_event	event;
	t_renderer	rend;
	t_app		app;
	SDL_Thread	*thread;
}				t_env;

#endif
