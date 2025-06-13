#include "minishell.h"
#include "exec.h"
#include "../libft/includes/libft.h"

#include <stdarg.h>

static void exit_proprely(int count, ...)
	{
	va_list args;
	void *ptr;
	rl_clear_history();
	va_start(args, count);
	while (count-- > 0) {
		ptr = va_arg(args, void *);
		free(ptr);
	}
	va_end(args);
	exit(0);
}

static t_utils *init_utils_struct(char **envp)
{
	t_utils *utils = malloc(sizeof(t_utils));

	if (!utils)
		return (NULL);

	utils->env = copy_env(envp);
	if (!utils->env)
	{
		free(utils);
		return (NULL);
	}
	utils->last_return = 0;
	utils->num_nodes = 0;
	utils->previous_pipes = -42;
	utils->status = 0;
	utils->type_of_first_arg = TOK_END;
	utils->old_stdin = dup(STDIN_FILENO); //TODO PROTECT?
	utils->old_stdout = dup(STDOUT_FILENO); //TODO PROTECT?

	return (utils);
}

static int is_all_spaces(const char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t')
			return (RETURN_FAILURE);
		str++;
	}
	return (RETURN_SUCCESS);
}

static char	quote_not_closed(const char *str)
{
	char	quote = 0;
	int		i = 0;

	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\'') && quote == 0)
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		i++;
	}
	return (quote);
}

static char	*strjoin_free(char *s1, const char *s2)
{
	char	*joined;
	
	if (!s1)
		return (ft_strdup(s2));
	joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}

static char	*read_input_with_quotes(void)
{
	char	*line;
	char	*tmp;
	char	quote;

	line = readline("minishell> ");
	if (!line)
		return (NULL);
	while ((quote = quote_not_closed(line)))
	{
		tmp = readline("> ");
		if (!tmp)
			break;
		line = strjoin_free(line, "\n");
		line = strjoin_free(line, tmp);
	}
	return (line);
}

int	main(int ac, char **av, char **env)
{
	char			*input;
	t_token			*token;
	t_utils			*utils;
	t_command_exec	*command;

	utils = init_utils_struct(env);
	(void)ac;
	(void)av;
	set_signals();
	while (1)
	{
		input = read_input_with_quotes();
		if (!input)
		{
			write(1, "exit\n", 5);
			exit_proprely(0, NULL, NULL);
		}
		if (*input)
			add_history(input);
		if (!*input || !is_all_spaces(input))
		{
			free(input);
			continue;
		}
		token = lexer(input);
		if (!token)
		{
			free(input);
			continue;
		}
		if (token->type != TOK_END && has_only_one_redirection(token))
		{
			print_syntax_error("newline", utils);
			free_tokens(token);
			free(input);
			continue;
		}
		if (ft_strcmp(input, "exit") == 0)
			exit_proprely(2, input, token);
		utils->type_of_first_arg = token->type;
		command = parse_tokens(token, utils);
		if (command)
		{
			if(exec(command, utils))
			{
				perror("EXEC ERROR\n");
				exit(EXIT_FAILURE);
			}

		}
		print_command_exec(command);
		free(input);
		free_tokens(token);
		free_commands_exec(command);
	}
	return (0);
}
