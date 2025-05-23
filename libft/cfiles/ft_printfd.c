/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 17:50:24 by ldevoude          #+#    #+#             */
/*   Updated: 2025/05/23 13:31:36 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/libft.h"


int	ft_printfd(const char *str, ...)
{
	va_list	ptr;
	int		i;
	int		return_value;
	int		*ptr_return_value;

	if (str == NULL)
		return (-1);
	va_start(ptr, str);
	return_value = 0;
	ptr_return_value = &return_value;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
			i += ft_printfd_cases(ptr, i, str, ptr_return_value);
		else
		{
			write(2, &str[i++], 1);
			return_value += 1;
		}
	}
	va_end(ptr);
	return (return_value);
}