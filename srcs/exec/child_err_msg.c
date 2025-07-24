/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_err_msg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 08:33:21 by ldevoude          #+#    #+#             */
/*   Updated: 2025/07/19 22:42:14 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

//	join three part of a msg
//	(usually the program and cmd + arg + reason of failure)
//	to write it directly in the FD2, the purpose here
//	is to not let multiple child overwrite eachothers
//	if write is used multiple time basicaly.
bool	join_err_msg_and_write(char *part_one_msg, char *part_two_msg,
		char *part_three_msg)
{
	char	*err_msg;
	char	*err_msg_buff;

	err_msg_buff = NULL;
	err_msg = malloc(ft_strlen(part_one_msg) + ft_strlen(part_two_msg)
			+ ft_strlen(part_three_msg));
	if (!err_msg)
		return (RETURN_FAILURE);
	err_msg_buff = err_msg;
	err_msg = ft_strjoin(part_one_msg, part_two_msg);
	free(err_msg_buff);
	err_msg_buff = err_msg;
	err_msg = ft_strjoin(err_msg, part_three_msg);
	free(err_msg_buff);
	if (!err_msg)
		return (RETURN_FAILURE);
	write(2, err_msg, ft_strlen(err_msg));
	free(err_msg);
	return (RETURN_SUCCESS);
}
