/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 04:52:44 by nboste            #+#    #+#             */
/*   Updated: 2016/12/18 04:52:47 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"
#include <stdlib.h>

void	ft_exit(char *msg)
{
	if (msg)
		ft_putendl(msg);
	exit(-1);
}
