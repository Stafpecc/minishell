#include "minishell.h"
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

	return (utils);
}

int main(int ac, char **av, char **env)
{
	char *input;
	t_token *token;
	t_utils *utils;

	utils = init_utils_struct(env);
	//print_utils_struct(utils);
	(void)ac;
	(void)av;
	set_signals();
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			write(1, "exit\n", 5);
			exit(0);
		}
		token = lexer(input);
		if (*input)
			add_history(input);
		if (!has_word_token(token))
			continue;
		if (ft_strcmp(input, "exit") == 0)
			exit_proprely(2, input, token);
		//print_tokens(token);
		t_command_exec *command = parse_tokens(token);
		if (command != NULL)
		{
			//ft_printfd("TEST\n");
			print_command_exec(command);
			exec(command, utils);
		}
		free(input);
		free_tokens(token);
		free_commands_exec(command);
	}
	return (0);
}