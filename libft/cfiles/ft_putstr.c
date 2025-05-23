/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:12:35 by tarini            #+#    #+#             */
/*   Updated: 2025/05/23 14:52:14 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_putstr(char *str)
{
	if (!str)
		return (ft_putstr("(null)"));
	if (write(1, str, ft_strlen(str)) == -1)
		return (-1);
	return (ft_strlen(str));
}
