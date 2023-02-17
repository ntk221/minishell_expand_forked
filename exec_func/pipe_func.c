/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satushi <satushi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 01:16:50 by satushi           #+#    #+#             */
/*   Updated: 2023/02/18 01:18:23 by satushi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static  void    cpy_pipe(int dst[2], int src[2])
{
	dst[0] = src[0];
	dst[1] = src[1];
}

void	prepare_pipe(t_node *node)
{
	if (node->next == NULL)//実行が一つ
		return ;
	if (pipe(node->command->out_fd) < 0)//outfdが外とつなぐ
		fatal_error("pipe");
	cpy_pipe(node->next->command->in_fd, node->command->out_fd);
}

void	prepare_pipe_child(t_node *node)
{
	close(node->command->out_fd[0]);
    //close(node->command->in_fd[1]);
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
		close(node->command->in_fd[0]); //前の出力を持ってくる
	if (node->next != NULL) //次がnullなら別にpipeでつなぐ必要はない
		close(node->command->out_fd[1]);
}