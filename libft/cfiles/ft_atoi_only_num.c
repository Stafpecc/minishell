/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_only_num.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:54:30 by tarini            #+#    #+#             */
/*   Updated: 2025/02/04 17:28:34 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_bool	ft_atoi_only_num(const char *str, int *result)
{
	const char	*ptr;

	if (!str || !*str)
		return (FALSE);
	ptr = str;
	while (*ptr)
	{
		if (!ft_isdigit(*ptr))
			return (FALSE);
		ptr++;
	}
	*result = ft_atoi(str);
	if (*result <= 0)
		return (FALSE);
	return (TRUE);
}

/*
#include <stdio.h>
#include <stdlib.h>

int	main(int ac, char **av) {
	(void)ac;
    int i = atoi(av[1]);
	int y = ft_atoi(av[1]);
 
    printf("with atoi function       :  %d\n", i);
	printf("with 42 atoi function    :  %d\n", y);
	return 0;
}
*/