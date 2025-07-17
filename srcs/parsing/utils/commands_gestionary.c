/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_gestionary.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:34:35 by stafpec           #+#    #+#             */
/*   Updated: 2025/07/17 16:47:49 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
//#include "../../../libft/includes/libft.h"

t_command	*create_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->cmd_parts = NULL;
	cmd->redirect_in = NULL;
	cmd->redirect_out = NULL;
	cmd->next = NULL;
	return (cmd);
}

int	get_size_of_redirect(t_arg **redirect)
{
	int	i;

	i = 0;
	if (redirect)
	{
		while (redirect[i])
			i++;
	}
	return (i);
}
