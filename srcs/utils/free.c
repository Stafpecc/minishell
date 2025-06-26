/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:13:04 by stafpec           #+#    #+#             */
/*   Updated: 2025/06/26 12:55:55 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

#include <stdarg.h>
#include <unistd.h>
#include <readline/readline.h>

void	free_env(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
		free(env[i++]);
	free(env);
}

void	free_utils(t_utils *utils)
{
	free_env(utils->env);
	close(utils->old_stdin);
	close(utils->old_stdout);
	free(utils);
}

void	exit_proprely(int count, ...)
{
	va_list		args;
	void		(*free_fn)(void *);
	void		*ptr;

	rl_clear_history();
	va_start(args, count);
	while (count-- > 0)
	{
		free_fn = va_arg(args, void (*)(void *));
		ptr = va_arg(args, void *);
		if (ptr && free_fn)
			free_fn(ptr);
	}
	va_end(args);
	exit(EXIT_SUCCESS);
}
