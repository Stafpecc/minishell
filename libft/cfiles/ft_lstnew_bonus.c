/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:16:13 by tarini            #+#    #+#             */
/*   Updated: 2024/11/29 15:13:07 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstnew(void *content)
{
	struct s_list	*my_new_list;

	my_new_list = malloc(sizeof(t_list));
	if (my_new_list == NULL)
		return (NULL);
	my_new_list->content = content;
	my_new_list->next = NULL;
	return (my_new_list);
}
