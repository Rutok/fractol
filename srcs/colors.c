/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 15:07:56 by nboste            #+#    #+#             */
/*   Updated: 2017/10/11 15:58:24 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_gen.h"

static t_color	hsl_more_more(t_hsl h, t_color c, t_color hsl)
{
	if (h.region == 3)
	{
		c.r = h.p;
		c.g = h.q;
		c.b = hsl.b;
	}
	else if (h.region == 4)
	{
		c.r = h.t;
		c.g = h.p;
		c.b = hsl.b;
	}
	else
	{
		c.r = hsl.b;
		c.g = h.p;
		c.b = h.q;
	}
	return (c);
}

t_color			hsl_more(t_hsl h, t_color c, t_color hsl)
{
	if (h.region == 0)
	{
		c.r = hsl.b;
		c.g = h.t;
		c.b = h.p;
	}
	else if (h.region == 1)
	{
		c.r = h.q;
		c.g = hsl.b;
		c.b = h.p;
	}
	else if (h.region == 2)
	{
		c.r = h.p;
		c.g = hsl.b;
		c.b = h.t;
	}
	else
		return (hsl_more_more(h, c, hsl));
	return (c);
}

t_color			get_color(double z)
{
	t_color	c;
	t_color	hsl;
	t_hsl	h;

	hsl.r = 100 + round(fabs(z));
	hsl.g = 100;
	hsl.b = 100;
	c.r = 0;
	h.region = hsl.r / 43;
	h.reminder = (hsl.r - (h.region * 43)) * 6;
	h.p = (hsl.g * (255 - hsl.b)) >> 8;
	h.q = (hsl.g * (255 - ((hsl.b * h.reminder) >> 8))) >> 8;
	h.t = (hsl.g * (255 - ((hsl.g * (255 - h.reminder)) >> 8))) >> 8;
	return (hsl_more(h, c, hsl));
}
