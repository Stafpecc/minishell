#include "../../include/exec.h"

static t_command_exec	*new_node(char *cmd, char *redir_in, char *redir_out, char **envp)
{
	t_command_exec	*node;

	node = malloc(sizeof(*node));
	if (!node)
		return (NULL);
	node->env = envp;//NULL;                // we'll pass envp later
	node->cmd_parts = ft_split(cmd, ' ');
	node->redirect_in = redir_in;
	node->redirect_out = redir_out;
	node->append_redirections = NULL;
	node->heredoc = NULL;
	node->next = NULL;
	return (node);
}

int	main(int argc, char **argv, char **envp)
{
	t_command_exec	*head;
	t_command_exec	*n1;
	t_command_exec	*n2;
	int				wstatus;

	(void)argc;
	(void)argv;
	/* Build: ls -l | grep ".c" > out.txt */
	n1 = new_node("ls -l", NULL, NULL, envp);
	n2 = new_node("grep .c", NULL, "out.txt", envp);
	// if (!n1 || !n2)
	// 	return (perror("malloc"), 1);

	n1->next = n2;
	head = n1;

	/* inject the real environment into each node */
	for (t_command_exec *it = head; it; it = it->next)
		it->env = envp;


	/* run the whole pipeline */
	exec(head, envp);
	/* parent: wait for all children */
	while (wait(&wstatus) > 0)
	{
		if (WIFEXITED(wstatus))
			printf("child exited with status %d\n", WEXITSTATUS(wstatus));
		else if (WIFSIGNALED(wstatus))
			printf("child killed by signal %d\n", WTERMSIG(wstatus));
	}
	//printf("test");

	return (0);
}
