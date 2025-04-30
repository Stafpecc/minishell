/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:29:11 by tarini            #+#    #+#             */
/*   Updated: 2024/11/17 13:46:30 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

/*
int main(void) {
	char test[] = {'A', 'z', '5', '!', ' ', 'G', 'm'};
	int i = -1;
	while (++i < 7) {
		if (ft_isalpha(test[i]))
			printf("'%c' letter.\n", test[i]);
		else
			printf("'%c' not a letter.\n", test[i]);
	}
	return 0;
}
*/
