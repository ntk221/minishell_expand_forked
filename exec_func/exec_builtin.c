/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satushi <satushi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:46:37 by user              #+#    #+#             */
/*   Updated: 2023/02/19 13:42:30 by satushi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	do_builtin(char *line, t_command *command)
{
	if (ft_strcmp(line, "env") == 0)
		ms_env();
	else if (ft_strncmp(line, "export", 6) == 0)
		ms_export(line, command);
	else if (ft_strncmp(line, "pwd", 3) == 0)
		ms_pwd();
	else if (ft_strncmp(line, "cd", 2) == 0)
		ms_cd(line, command);
	else if (ft_strncmp(line, "exit", 4) == 0)
		ms_exit(line, command);
	else if (ft_strncmp(line, "unset", 5) == 0)
		ms_unset(line, command);
	else if (ft_strncmp(line, "echo", 4) == 0)
		ms_echo(line, command);
	return (0);
}
