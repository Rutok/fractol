/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 06:01:31 by nboste            #+#    #+#             */
/*   Updated: 2016/12/22 14:15:12 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drawer.h"
#include "libft.h"
#include "error.h"

void	drawer_init(t_env *env)
{
	if (!(env->rend.rend_sdl = SDL_CreateRenderer(env->win.win_sdl, -1, SDL_RENDERER_ACCELERATED)))
		ft_exit(MSG_SDL_INIT_FAILED);
	if (!(env->rend.texture_sdl = SDL_CreateTexture(env->rend.rend_sdl, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, env->win.size.x, env->win.size.y)))
		ft_exit(MSG_SDL_INIT_FAILED);
	if (!(env->rend.pixels = (uint32 *)malloc(sizeof(uint32) * env->win.size.x * env->win.size.y)))
		ft_exit(MSG_MALLOC);
	if (!(env->rend.pixels2 = (uint32 *)malloc(sizeof(uint32) * env->win.size.x * env->win.size.y)))
		ft_exit(MSG_MALLOC);

	env->rend.size.x = env->win.size.x;
	env->rend.size.y= env->win.size.y;
	env->rend.ready = 1;
}

void	drawer_process(t_renderer *rend)
{
	if (rend->draw)
	{
		SDL_UpdateTexture(rend->texture_sdl, NULL, rend->pixels2, rend->size.x * sizeof(uint32));
		rend->draw = 0;
		SDL_RenderCopy(rend->rend_sdl, rend->texture_sdl, NULL, NULL);
		SDL_RenderPresent(rend->rend_sdl);
	}
}

void	drawer_destroy(t_renderer *rend)
{
	free(rend->pixels);
	free(rend->pixels2);
	SDL_DestroyRenderer(rend->rend_sdl);
}

void	drawer_put_pixel(t_2ipair coord, uint32 color, t_renderer *rend)
{
	if (coord.x >= 0 && coord.x < rend->size.x && coord.y >= 0 && coord.y < rend->size.y)
		rend->pixels[coord.x + rend->size.x * coord.y] = color;
}

void	drawer_clean(t_renderer *rend)
{
	t_2ipair c;

	c.y = 0;
	while (c.y < rend->size.y)
	{
		c.x = 0;
		while (c.x < rend->size.x)
		{
			drawer_put_pixel(c, 0, rend);
			c.x++;
		}
		c.y++;
	}
}

void	drawer_wait_copy(t_env *env)
{
	while (env->rend.draw)
	{
		SDL_Delay(3);
	}
	memcpy(env->rend.pixels2, env->rend.pixels, sizeof(uint32) * env->win.size.x * env->win.size.y);
	env->rend.draw = 1;
}
