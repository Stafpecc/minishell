/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:06:24 by tarini            #+#    #+#             */
/*   Updated: 2024/11/29 15:12:05 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}

/*
int main(void)
{
    char test[] = {'A', 'z', '5', '!', ' ', '\n', '\t', 127};
    int i = -1;
    
    while (++i < 8) {
        if (ft_isprint(test[i]))
            printf("'%c' is printable.\n", test[i]);
        else
            printf("'%c' is not printable.\n", test[i]);
    }
    
    return 0;
}
*/
