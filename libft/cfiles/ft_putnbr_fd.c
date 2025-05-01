/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:27:10 by tarini            #+#    #+#             */
/*   Updated: 2024/11/29 15:14:03 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		if (n == -2147483648)
		{
			ft_putchar_fd(45, fd);
			ft_putnbr_fd(2147, fd);
			ft_putnbr_fd(483648, fd);
		}
		else
		{
			ft_putchar_fd(45, fd);
			n = -1 * n;
			ft_putnbr_fd(n, fd);
		}
	}
	else if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd(48 + n % 10, fd);
	}
	else
	{
		ft_putchar_fd(48 + n, fd);
	}
}
