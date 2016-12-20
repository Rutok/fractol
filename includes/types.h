/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 04:36:59 by nboste            #+#    #+#             */
/*   Updated: 2016/12/20 13:49:22 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <SDL2/SDL.h>
# include "libft.h"

typedef unsigned char	t_bool;

typedef unsigned int	uint32;

typedef struct	s_2ipair
{
	int	x;
	int	y;
}				t_2ipair;

typedef struct	s_2dpair
{
	double	x;
	double	y;
}				t_2dpair;

typedef struct	s_3dvertex
{
	double	x;
	double	y;
	double	z;
}				t_3dvertex;

typedef struct	s_win
{
	SDL_Window	*win_sdl;
	t_2ipair	size;
	char		*name;
}				t_win;

typedef struct	s_renderer
{
	SDL_Renderer	*rend_sdl;
	SDL_Texture		*texture_sdl;
	uint32			*pixels;
	t_2ipair		size;
}				t_renderer;

typedef struct	s_event
{
	t_bool		exit;
	t_bool		move_left;
	t_bool		move_right;
	t_bool		move_up;
	t_bool		move_down;
	t_bool		plus;
	t_bool		minus;
	t_bool		mouse_move;
	t_2ipair	mouse_pos;
	t_bool		key_f1;
	t_bool		key_f2;
	t_bool		draw;
}				t_event;

typedef struct s_env t_env;

typedef struct	s_app
{
	void	(*init)(t_env *);
	void	(*process)(t_env *);
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
}				t_env;

#endif
