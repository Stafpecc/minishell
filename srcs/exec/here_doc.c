/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 09:23:09 by ldevoude          #+#    #+#             */
/*   Updated: 2025/06/11 17:21:44 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"
//we init input to NULL, then we get into an infinite while loop
//(can do a bool if norme require it) then we write inside of input
//what the user prompt we secure it, we check if fd and delimiter = the same
// if yes we break the loop to finish the program 
// if no we write the content of input with a \n free input set it to null
// then we go back to the start of the loop UNTIL we find the EOF delimiter

static int readline_heredoc(int fd, char *delimiter)
{
    char *input;

    while (1)
    {
        input = readline("> ");
        if (!input)
        {
            write(1, "\n", 1);
            break;
        }
        if (ft_strcmp(input, delimiter) == 0)
        {
            free(input);
            break;
        }
        write(fd, input, ft_strlen(input));
        write(fd, "\n", 1);
        free(input);
    }
    return (0);
}

//I create .heredoc.tmp with open and associate its fd into fd, I secure it
//we go to readline_heredoc that should return us 0 if everything went well
//inside of it we gonna fill .heredoc.tmp with user's input(s)
//once outside we close close fd and do a new open that is RDONLY this time
//if fail return -1, else unlink (fd would still work even with unlink)
//to remove .heredoc.tmp from the directory then we return the FD that
//should be used in dup to get the content as the read content!
int here_doc (char *delimiter)
{
    int  fd;

    fd = open(".heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if(fd < 0)
        return(-1);
    if (readline_heredoc (fd,delimiter))
    {
        unlink(".heredoc.tmp");
        close (fd);
        return(-1);
    }
    close (fd);
    fd = open(".heredoc.tmp", O_RDONLY);
    if(fd < 0)
        return (-1);
    unlink(".heredoc.tmp");
    return (fd);
}
