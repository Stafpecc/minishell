// typedef struct s_command {
//     char **cmd;
//     char *redirect_in;
//     char *redirect_out;
//     struct s_command *next;
// } t_command;

// echo with option -n
// ◦ cd with only a relative or absolute path
// ◦ pwd with no options
// ◦ export with no options
// ◦ unset with no options
// ◦ env with no options or arguments
// ◦ exit with no options

#include "../include/exec.h"

// typedef struct s_arg {
//     char *arg;
//     bool in_simple_quote;
//     bool in_double_quote;
// } t_arg;

// typedef struct s_cmd_part {
//     char *content;
//     bool in_simple_quote;
//     bool in_double_quote;
// } t_cmd_part;

// typedef struct s_command {
//     t_cmd_part    **cmd_parts;
//     char        *redirect_in;
//     char        *redirect_out;
//     t_arg        *append_redirections;
//     t_arg        *heredoc;
//     struct s_command *next;
// } t_command;

// check if it is a built-in cmd
// TODO also need a struct with env + last return


void	child_maker(t_command *node, int number_nodes)
{
	int		i;
	int		pipe_fd[2];
	int		previous_pipe;
	pid_t	child;

	//printf("test");
	i = 0;
	previous_pipe = -42; //TODO #define NO_PREV_PIPE
	//printf("NOMBRE NODES: %d\n", number_nodes);
	pipe(pipe_fd);
	while (node)
	{
		if (previous_pipe != -1 ||i < number_nodes - 1)
		{
			pipe(pipe_fd); // TODO protect
		}
		child = fork();    // protect
		if (child == 0)
			child_init_pipes_dup(node, pipe_fd, previous_pipe);
		else
		{
			// parent close what we dont need anymore
			
			if (i < number_nodes - 1)
				close(pipe_fd[1]);
			if (previous_pipe != -1)
				close(previous_pipe);
			previous_pipe = pipe_fd[0];
			//close(pipe_fd[0]); //TODL I may did a mistake here bleh
			node = node->next;
			i++;
		}
	}
	// TODO WAIT CHILDS WAITPID
}

bool	built_in_checker(char *cmd)
{
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd,
			"export") || !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"))
		return (true);
	else
		return (false);
}

// To count how much commands has been sent
// INFO : I am unsure about the parameter name
int	count_commands(t_command *cmds, bool *is_alone)
{
	int	count;

	count = 0;
	while (cmds)
	{
        count++;
        cmds = cmds->next;
	}
    *is_alone = (count == 1);
	return (count);
}

// exec that does receive a *node 
//TODO also the struct that contain the env and last return
// can remove is_alone if not enough
// space they exist for lisibility purpose

void	exec(t_command *node)
{
	int		number_nodes;
	bool	is_alone;

	number_nodes = count_commands(node, &is_alone);
	if (is_alone == true)
	{
		if (built_in_checker(node->cmd_parts[0]->arg))
		{
			ft_printf("Parent: built_in_checker passed\n"); //TORMASAP
			// TODObuilt_in redirect
		}
		else
		{
			printf("parent: not a single built-in\n"); //TORMASAP
			child_maker(node, number_nodes);
		}
			
	}
	exit(EXIT_FAILURE);
}