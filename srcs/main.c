#include "minishell.h"
#include "exec.h"
#include "../libft/includes/libft.h"

#include <stdarg.h>

void	exit_proprely(int count, ...)
{
	va_list args;
	void (*free_fn)(void *);
	void *ptr;

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

static void free_env(char **env)
{
	int i = 0;
	if (!env)
		return;
	while (env[i])
		free(env[i++]);
	free(env);
}

static void free_utils(t_utils *utils)
{
	free_env(utils->env);
	close(utils->old_stdin);
	close(utils->old_stdout);
	free(utils);
}

static char **add_var_to_env(char **env, const char *var)
{
	int		i = 0;
	char	**new_env;

	while (env && env[i])
		i++;

	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (NULL);

	i = 0;
	while (env && env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			free_env(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = ft_strdup(var);
	if (!new_env[i])
	{
		free_env(new_env);
		return (NULL);
	}
	new_env[i + 1] = NULL;
	free_env(env);
	return (new_env);
}


static t_utils *init_utils_struct(char **envp)
{
	t_utils *utils = malloc(sizeof(t_utils));
	char **tmp;

	if (!utils)
		return (NULL);

	utils->env = copy_env(envp);
	if (!utils->env)
	{
		free(utils);
		return (NULL);
	}
	tmp = add_var_to_env(utils->env, "MINISHELL_RUNNING=1");
	if (!tmp)
	{
		free_env(utils->env);
		free(utils);
		return (NULL);
	}
	utils->env = tmp;
	utils->last_return = 0;
	utils->num_nodes = 0;
	utils->previous_pipes = -42;
	utils->status = 0;
	utils->type_of_first_arg = TOK_END;
	utils->old_stdin = dup(STDIN_FILENO); //TODO PROTECT
	utils->old_stdout = dup(STDOUT_FILENO); //TODO PROTECT
	utils->size_env = ft_env_len(utils->env);

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

	if (ac != 1)
	{
		ft_printfd(RED "Error: minishell does not take any arguments\n" RESET);
		return (RETURN_FAILURE);
	}
	if (!isatty(STDIN_FILENO))
	{
		ft_printfd(RED "Error: minishell must be run in an interactive terminal\n" RESET);
		return (RETURN_FAILURE);
	}
	if (getenv("MINISHELL_RUNNING") != NULL)
	{
		ft_printfd(RED "Error: minishell cannot be run recursively\n" RESET);
		return (RETURN_FAILURE);
	}
	utils = init_utils_struct(env);
	(void)av;
	set_signals();
	while (1)
	{
		ft_printfd("LASTRETURN= %d\n",utils->last_return);
		input = read_input_with_quotes();
		if (!input)
		{
			write(1, "exit\n", 5);
			exit_proprely(0);
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
		{
			exit_proprely(3,
				(void (*)(void *))free, input,
				(void (*)(void *))free_tokens, token,
				(void (*)(void *))free_utils, utils);
		}
		utils->type_of_first_arg = token->type;
		command = parse_tokens(token, utils);
		print_command_exec(command);
		if (command)
		{
			if(exec(command, utils) == MALLOC_ERROR) //TODO different treatments depending of the error, there is two kind of errors possible the one that wont stop program the one that does.
			{
				perror("EXEC ERROR\n");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			free(input);
			free_tokens(token);
			continue;
		}
		free(input); //TODO CLOSE les dups OLDSTDIN OLDSTDOUT DANS UTILS
		free_tokens(token);
		free_commands_exec(command);
	}
	return (0);
}
