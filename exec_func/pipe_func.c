/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 01:16:50 by satushi           #+#    #+#             */
/*   Updated: 2023/02/28 22:08:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	void	cpy_pipe(int dst[2], int src[2])
{
	dst[0] = src[0];
	dst[1] = src[1];
}

void	prepare_pipe(t_node *node)
{
	if (node->next == NULL)
		return ;
	if (pipe(node->command->out_fd) < 0)
		fatal_error("pipe");
	cpy_pipe(node->next->command->in_fd, node->command->out_fd);
}

void	prepare_pipe_child(t_node *node)
{
	close(node->command->out_fd[0]);
	dup2(node->command->in_fd[0], STDIN_FILENO);
	if (node->command->in_fd[0] != STDIN_FILENO)
		close(node->command->in_fd[0]);
	dup2(node->command->out_fd[1], STDOUT_FILENO);
	if (node->command->out_fd[1] != STDOUT_FILENO)
		close(node->command->out_fd[1]);
}

void	prepare_pipe_parent(t_node *node)
{
	if (node->command->in_fd[0] != STDIN_FILENO)
		close(node->command->in_fd[0]);
	if (node->next != NULL)
		close(node->command->out_fd[1]);
}

void	wait_pipeline(pid_t last_pid)
{
	pid_t	wait_result;
	int		wstatus;
	int		signal;

	while (1)
	{
		wait_result = wait(&wstatus);
		if (wait_result == last_pid)
			g_env->err_status = WEXITSTATUS(wstatus);
		else if (WIFSIGNALED(wstatus))
		{
			signal = WTERMSIG(wstatus);
			if (signal == SIGQUIT)
				ft_putendl_fd("Quit: 3", STDERR_FILENO);
			if (signal == SIGINT)
				ft_putendl_fd("", STDERR_FILENO);
			g_env->err_status = signal + 128;
			break ;
		}
		else if (wait_result < 0)
			if (errno == ECHILD)
				break ;
	}
}
