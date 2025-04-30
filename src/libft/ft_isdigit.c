/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:15:02 by tarini            #+#    #+#             */
/*   Updated: 2024/11/17 13:46:31 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
/*
#include <stdio.h>
#include "libft.h"

int main(void) {
    char test[] = {'A', 'z', '5', '!', ' ', 'G', 'm'};
    int i = -1;
    
    while (++i < 7) {
        if (ft_isdigit(test[i]))
            printf("'%c' digit.\n", test[i]);
        else
            printf("'%c' not a digit.\n", test[i]);
    }
    
    return 0;
}

*/
