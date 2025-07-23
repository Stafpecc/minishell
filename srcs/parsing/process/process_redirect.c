
#include "exec.h"

/*
Function that:
- moves to the next token after an input redirection (<);
- checks that the token is a valid word, otherwise displays a syntax error;
- allocates or uses the redirect_in array to store the redirection argument
  at the static position location_of_the_table;
- copies the argument, processes quotes, adds the argument to cmd_parts,
  and marks the last argument as final;
- advances the token and increments location_of_the_table;
- returns RETURN_SUCCESS or frees memory and returns an error in case of failure.
*/
int	process_redirect_in(t_token **tokens, t_command *curr,
	t_command *head, t_utils *utils)
{
	t_context			ctx;
	t_redirect_flags	flags;

	ctx.head = head;
	ctx.utils = utils;
	flags.is_heredoc = false;
	flags.is_append = false;
	return (add_redirect(tokens, &curr->redirect_in, &ctx, flags));
}

/*
Function that:
- moves to the next token after an output redirection (>);
- checks the validity of the token, displays an error if needed;
- allocates or uses the redirect_out array with a static index
  location_of_the_table to store the argument;
- copies the argument, processes quotes, adds it to cmd_parts, and marks the
  last argument as final;
- increments location_of_the_table and returns RETURN_SUCCESS or an error
  if a problem occurs.
*/
int	process_redirect_out(t_token **tokens, t_command *curr,
	t_command *head, t_utils *utils)
{
	t_context			ctx;
	t_redirect_flags	flags;

	ctx.head = head;
	ctx.utils = utils;
	flags.is_heredoc = false;
	flags.is_append = false;
	return (add_redirect(tokens, &curr->redirect_out, &ctx, flags));
}

/*
Function that:
- moves to the next token after an append redirection (>>);
- checks that the following token is valid, otherwise displays an error;
- allocates append_redirections if needed, copies the argument, and processes
  any quotes;
- adds the argument to cmd_parts, marks the last argument as final;
- advances the token and returns RETURN_SUCCESS or an error if a problem occurs.
*/
int	process_append_redirect(t_token **tokens, t_command *curr,
	t_command *head, t_utils *utils)
{
	t_context			ctx;
	t_redirect_flags	flags;

	ctx.head = head;
	ctx.utils = utils;
	flags.is_heredoc = false;
	flags.is_append = true;
	return (add_redirect(tokens, &curr->redirect_out, &ctx, flags));
}

/*
Function that:
- advances through the token list to handle a heredoc after the << redirection;
- checks that the next token is valid (expected word) and manages syntax errors;
- allocates and initializes the heredoc structure in the current command with
the token value;
- processes any quotes in the token and adds the argument to the command;
- marks the last argument as finalized and advances the current token;
- returns RETURN_SUCCESS if everything went well, otherwise frees memory and
returns an error.
*/
int	process_heredoc(t_token **tokens, t_command *curr,
	t_command *head, t_utils *utils)
{
	t_context			ctx;
	t_redirect_flags	flags;
	int					i;
	int					fd;

	ctx.head = head;
	ctx.utils = utils;
	flags.is_heredoc = true;
	flags.is_append = false;
	i = 0;
	while (curr->redirect_in && curr->redirect_in[i])
		i++;
	if (add_redirect(tokens, &curr->redirect_in, &ctx, flags) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	process_quotes(*tokens, curr->redirect_in[i]);
	fd = here_doc(curr->redirect_in[i]->arg);
	utils->fd = fd;
	if (fd < 0 || fd == 130)
	{
		if (fd < 0)
			utils->last_return = fd * -1;
		else
			utils->last_return = fd;
		return (RETURN_FAILURE);
	}
	curr->redirect_in[i]->fd = fd;
	return (RETURN_SUCCESS);
}
