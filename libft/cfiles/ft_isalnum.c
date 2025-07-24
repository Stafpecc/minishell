/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 19:48:54 by tarini            #+#    #+#             */
/*   Updated: 2024/11/29 15:11:48 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) == 1 || ft_isdigit(c) == 1);
}
/*
int	main(int ac, char **av) {
	(void)ac;
	ft_atoi(av[1]);
}
*/
