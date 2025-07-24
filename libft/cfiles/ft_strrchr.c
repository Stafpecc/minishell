/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:31:33 by stafpec           #+#    #+#             */
/*   Updated: 2024/11/29 15:15:08 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strrchr(const char *str, int c)
{
	const char	*last;
	size_t		i;

	last = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == (unsigned char)c)
			last = &str[i];
		i++;
	}
	if (!(unsigned char)c)
		return ((char *)(&str[i]));
	return ((char *)last);
}
