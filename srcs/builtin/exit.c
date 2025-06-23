#include "builtin.h"
#include "minishell.h"

static int print_exit(long long code, char *arg, bool too_many_arguments)
{
    ft_printf("exit\n");
    if(code == 2)
        ft_printfd("minishell: exit: %s: numeric argument required\n", arg);
    if(too_many_arguments)
    {
        ft_printfd("minishell: exit: too many arguments\n");
        return(RETURN_FAILURE);
    }
    exit(code);
}

//19 digits max value  9223372036854775807
//20 min value -9223372036854775808 exit
//exit (-1) return 255
static void overflow_check(char *arg)
{
    int counter_digits;

    counter_digits = 0;
    while(arg[counter_digits])
        counter_digits++;
    if (arg[0] == '-')
    {       
        if (counter_digits > 19 ||(counter_digits == 19 && ft_atoi(arg) > 0))
            print_exit(2, arg, FALSE);
    }
    else if (counter_digits > 18 || (counter_digits == 18 && ft_atoi(arg) < 0))
        print_exit(2, arg, FALSE);

    // if (arg[0] == '-' \
    //     && (counter_digits > 20 \
    //     ||(counter_digits == 20 && ft_atoi(arg) > 0)))
    // {
    //     printf("1");
    //     print_exit(2, arg, FALSE);
    // }

    // if (arg[0] != '-' \
    //     && (counter_digits > 18 \
    //     || (counter_digits == 18 && ft_atoi(arg) < 0)))
    // {
    //     printf("2");
    //     print_exit(2, arg, FALSE);
    // }
}

static void is_arg_digit_and_overflow(char *arg)
{
    int i;

    i = 0;
    if(arg[0] == '-' || arg[0] == '+')
        i++;
    while(arg[i])
    {
        if(!ft_isdigit(arg[i]))
            print_exit(2, arg, FALSE);
        i++;
    }
    overflow_check(arg);
}

//exit_builtin would check if we at least have an arg
//if not like bash we exit with the last return
//then we check if our first arg is a digit 
//and if it does overflow
//then we check if there is more than a single arg
//if yes then return failure and get back to 
//minishell prompt
//we save the result of ft_atoi into exit_value

unsigned int exit_builtin(t_command_exec *node, t_utils *utils)
{
    long long return_value;

    return_value = 0;
    if(!node->cmd_parts[1])
        print_exit(utils->last_return, NULL, FALSE);
    is_arg_digit_and_overflow(node->cmd_parts[1]);
    if(node->cmd_parts[2])
        return (print_exit(0, NULL, TRUE));
    return_value = ft_atoi(node->cmd_parts[1]);
    if (return_value < 0)
        print_exit(return_value + 256, NULL, FALSE);
    else
        print_exit(return_value - 256, NULL, FALSE);
    return(RETURN_SUCCESS);
}
