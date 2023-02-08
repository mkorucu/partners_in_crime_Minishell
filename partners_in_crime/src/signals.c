/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkorucu <mkorucu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:17:24 by mkorucu           #+#    #+#             */
/*   Updated: 2023/02/08 11:50:42 by mkorucu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	close_heredoc(int sig)
{
	(void)sig;
	g_crime.ignore = 1;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
}

void	handle_sigint(int sig)  //ctrl_c
{
	if (sig == SIGINT)
	{
		g_crime.fail = 1;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		write(1, "\033[A", 3);
	}
}

void	handle_exit(char *str)
{
	if (!str)
	{
		printf("exit\n");
		exit(errno);
	}
}