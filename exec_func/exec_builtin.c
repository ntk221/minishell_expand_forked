/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:46:37 by user              #+#    #+#             */
/*   Updated: 2023/02/16 20:48:13 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	do_builtin(char *line, t_command *command)
{
	if (strcmp(line, "env") == 0)
		ms_env();
	else if (strncmp(line, "export", 6) == 0)
		ms_export(line, command);
	else if (strcmp(line, "pwd") == 0)
		ms_pwd();
	else if (strncmp(line, "cd", 2) == 0)
		ms_cd(line, command);
	else if (strncmp(line, "exit", 4) == 0)
		ms_exit(line, command);
	else if (strncmp(line, "unset", 5) == 0)
		ms_unset(line, command);
	else if (strncmp(line, "echo", 4) == 0)
		ms_echo(line, command);
}
