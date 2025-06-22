#include "builtin.h"
#include "minishell.h"


    //check si argument is nbr si c'est pas nbr leave avec 255
static void print_exit(long long code, char *arg)
{
    ft_printf("exit\n");
    if(code == 255)
        ft_printfd("minishell: exit: %s: numeric argument required\n",arg);
    exit(code);
}

static unsigned int cases_no_args_two_args(t_command_exec *node, t_utils *utils)
{
    if(!node->cmd_parts[1])
        print_exit(utils->last_return, NULL);
    else if (node->cmd_parts[2])
    {
        ft_printf("exit\n");
        ft_printfd("minishell: exit: too many arguments\n");
        return(RETURN_FAILURE);
    }
    return(RETURN_SUCCESS);
}
//19 digits max value  9223372036854775807
//20 min value -9223372036854775808
//exit (-1) return 255
static bool overflow_check(char *arg)
{
    int i;

    i = 0;
    while(arg[i])
        i++;
    if (arg[0] == '-')
    {
        if (i > 19)
           return(TRUE);
    }
    if (i > 18)
        return(TRUE);
    return (FALSE);
}

static void is_arg_digit_and_overflow(char *arg)
{
    int i;

    i = 0;
    while(arg[i])
    {
        if(arg[0] == '-')
            i++;
        if(!ft_isdigit(arg[i]))
            print_exit(255, arg);
        i++;
    }
    if(overflow_check(arg))
        print_exit(255, arg);
}

unsigned int exit_builtin(t_command_exec *node, t_utils *utils)
{
    long long return_value;

    return_value = 0;
    if(!node->cmd_parts[1] || node->cmd_parts[2])
        return(cases_no_args_two_args(node, utils));
    if (node->cmd_parts[1] == 0)
        print_exit(0, NULL);
    is_arg_digit_and_overflow(node->cmd_parts[1]);
    return_value = ft_atoi(node->cmd_parts[1]); //TODO ask theo about that way
    ft_printfd("return_value = %d\n", return_value); 
    if (return_value == 0)
        print_exit(2, NULL);
    else
        print_exit(return_value, NULL);
    return(RETURN_FAILURE);
}
