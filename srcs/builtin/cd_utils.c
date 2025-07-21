/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:05:46 by ldevoude          #+#    #+#             */
/*   Updated: 2025/07/21 09:16:25 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

//    function's goal is to treat errors correctly
//    depending of the received error to send the right
//    msg to the user

int	return_errors(int return_value, int message, t_command_exec *node)
{
	if (message == ERR_CD_CHDIR)
	{
		if (join_err_msg_and_write("minishell: cd: ", node->cmd_parts[1],
				": No such file or directory\n"))
			return (MALLOC_ERROR);
	}
	else if (message == ERR_CD_GETCWD)
	{
		if (join_err_msg_and_write("error retrieving current directory: ",
				"getcwd: cannot access parent directories: ",
				"No such file or directory\n"))
			return (MALLOC_ERROR);
	}
	else if (message == ERR_CD_MALLOC)
		write(2, "bash: cd: cannot allocate memory\n", 34);
	return (return_value);
}
