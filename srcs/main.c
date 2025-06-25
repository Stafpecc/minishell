#include "minishell.h"
#include "exec.h"
#include "parsing.h"
#include "../libft/includes/libft.h"

int	main(int ac, char **av, char **env)
{
	t_utils	*utils;

	(void)av;
	if (check_error(ac) == RETURN_FAILURE)
		return (RETURN_FAILURE);
	utils = init_utils_struct(env);
	minishell_loop(utils);
	return (0);
}
