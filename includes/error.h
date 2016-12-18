/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 04:52:32 by nboste            #+#    #+#             */
/*   Updated: 2016/12/18 06:25:26 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_H
# define FT_ERROR_H

# define MSG_SDL_INIT_FAILED "SDL_Init(); Failed."
# define MSG_SDL_REND_FAILED "SDL_Renderer Failed."
# define MSG_MALLOC "Malloc failed."

void	ft_exit(char *msg);

#endif
