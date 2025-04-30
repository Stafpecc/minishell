/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:35:13 by tarini            #+#    #+#             */
/*   Updated: 2024/11/17 13:46:30 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}

/*
#include <stdio.h>

int main() {
    char test_chars[] = {0, 32, 65, 127, 128, -1};
    int i = 0;
    while (i < 6) {
        if (ft_isascii(test_chars[i])) {
            printf("'%c' is a valid ASCII character.\n", test_chars[i]);
        } else {
            printf("'%c' is not a valid ASCII character.\n", test_chars[i]);
        }
        i++; 
    }

    return 0;
}
*/
