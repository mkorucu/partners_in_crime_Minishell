/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkorucu <mkorucu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 19:15:09 by btekinli          #+#    #+#             */
/*   Updated: 2023/02/07 14:07:52 by mkorucu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	contain_heredoc(t_process *process)
{
	int	i;

	i = 0;
	while (process->redirects[i])
	{
		if (is_operator(process->redirects[i]) == HERE_DOC)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

void	close_fd_all(void)
{
	t_process	*process;

	process = g_ms.process;
	while (process)
	{
		if (contain_heredoc(process) && process->heredoc_fd[0] > 2)
			close(process->heredoc_fd[0]);
		if (process->fd[0] > 2)
			close(process->fd[0]);
		if (process->fd[1] > 2)
			close(process->fd[1]);
		process = process->next;
	}
}

void	route_cmd(t_process *process)
{
	if (g_ms.process_count > 1)
	{
		if (contain_heredoc(process))
		{
			dup2(process->heredoc_fd[0], 0);
			if (process->next != NULL)
				dup2(process->fd[1], 1);
		}
		else
		{
			if (process->prev == NULL)
				dup2(process->fd[1], 1);
			else if (process->next == NULL)
				dup2(process->prev->fd[0], 0);
			else
			{
				dup2(process->prev->fd[0], 0);
				dup2(process->fd[1], 1);
			}
		}
	}
	get_all_inputs(process);
	set_all_outputs(process);
	close_fd_all();
}

void	run_cmd(t_process *process)
{
	pid_t	pid;
	char	*path;

	pid = fork();
	if (pid == CHILD_PROCESS)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		route_cmd(process);
		run_builtin(process->execute);
		path = get_path(*process->execute);
		execve(path, process->execute, g_ms.env);
		cmd_error(*process->execute);
		exit(errno);
	}
	else
		process->pid = pid;
}
