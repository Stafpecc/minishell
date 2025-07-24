/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ascii_art.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:09:08 by ldevoude          #+#    #+#             */
/*   Updated: 2025/07/21 10:54:42 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

static void	write_and_free(char *line)
{
	write(1, line, ft_strlen(line));
	free(line);
}

static void	fill_line(char *line, char *content)
{
	line = ft_strdup(content);
	if (!line)
	{
		perror("");
		exit(1);
	}
	write_and_free(line);
}

void	ascii_minishell(char *line)
{
	fill_line (line, RED"            __  __ ___ _   _ ___");
	fill_line(line, " ____  _   _ _____ _     _             \n");
	fill_line(line, "           |  \\/  |_ _| \\ | |_ _/");
	fill_line(line, " ___|| | | | ____| |   | |            \n");
	fill_line(line, "           | |\\/| || ||  \\| || ");
	fill_line(line, "|\\___ \\| |_| |  _| | |   | |            \n");
	fill_line(line, "           | |  | || || |\\  ");
	fill_line(line, "|| | ___) |  _  | |___| |___| |___         \n");
	fill_line(line, MAG"  _        "RED);
	fill_line(line, "|_|  |_|___|_");
	fill_line(line, "| \\_|___|____/|_| |_|_____|_____|_____|        \n"RESET);
}

void	ascii_tarini(char *line)
{
	fill_line(line, MAG" | |__  _   _  |_   _|/ \\  |  _ \\|_");
	fill_line(line, " _| \\ | |_ _|                       \n");
	fill_line(line, " | '_ \\| | | |   | | / _ \\ | |_) ||");
	fill_line(line, " ||  \\| || |                        \n");
	fill_line(line, " | |_) | |_| |   | |/ ___ \\|");
	fill_line(line, "  _ < | || |\\  || |                        \n");
	fill_line(line, " |_.__/ \\__, |   |_/_/_  \\_\\_");
	fill_line(line, "|_\\_\\___|_|_\\_|___|");
	fill_line(line, CYN"___  _   _ ____  _____ \n");
}

void	ascii_ldevoude(char *line)
{
	fill_line(line, "   __ _ ");
	fill_line(line, MAG"|___/"CYN);
	fill_line(line, "  __| | | |   |  _ \\| ____\\ \\  ");
	fill_line(line, " / / _ \\| | | |  _ \\| ____|\n");
	fill_line(line, "  / _` | '_ \\ / _` | | |   | | | |  _");
	fill_line(line, "|  \\ \\ / / | | | | | | | | |  _|  \n");
	fill_line(line, " | (_| | | | | (_| | | |___| |_| | ");
	fill_line(line, "|___  \\ V /| |_| | |_| | |_| | |___ \n");
	fill_line(line, "  \\__,_|_| |_|\\__,_| |_____|____/|");
	fill_line(line, "_____|  \\_/  \\___/ \\___/|____/|_____|\n\n\n\n"RESET);
}
