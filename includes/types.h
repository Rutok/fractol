/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 04:36:59 by nboste            #+#    #+#             */
/*   Updated: 2016/12/18 23:05:13 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <SDL2/SDL.h>
# include "libft.h"

typedef unsigned char	t_bool;

typedef unsigned int	uint32;

typedef enum			e_fractales
{
	mandelbrot,
	julia
}						t_fractales;

typedef struct	s_2ipair
{
	int	x;
	int	y;
}				t_2ipair;

typedef struct	s_win
{
	SDL_Window	*win_sdl;
	t_2ipair		size;
}				t_win;

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
	t_bool		switch_mandelbrot;
	t_bool		switch_julia;
	t_bool		no_event;
}				t_event;

typedef struct	s_renderer
{
	SDL_Renderer	*rend_sdl;
	SDL_Texture		*texture_sdl;
	uint32			*pixels;
	t_2ipair			size;
}				t_renderer;

typedef struct	s_frac_gen
{
	t_pair	max;
	t_pair	min;
	int		it;
	int		base_it;
	t_fractales current;
}				t_frac_gen;

typedef struct s_env
{
	t_win	win;
	t_event	event;
	t_renderer	rend;
	t_frac_gen	gen;
}				t_env;

#endif
