/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 20:45:54 by stafpec           #+#    #+#             */
/*   Updated: 2024/11/21 12:06:02 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*map_node(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	void	*new_content;
	t_list	*new_node;

	new_content = f(lst->content);
	if (!new_content)
		return (NULL);
	new_node = ft_lstnew(new_content);
	if (!new_node)
	{
		del(new_content);
		return (NULL);
	}
	return (new_node);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;

	if (!lst || !f)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		new_node = map_node(lst, f, del);
		if (!new_node)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}
