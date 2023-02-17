/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:18:23 by user              #+#    #+#             */
/*   Updated: 2023/02/17 22:34:13 by kazuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_cd(char *line, t_command *command)
{
	char	**commands;
	char	*path;

	(void)line;
	commands = command_to_array(command);
	// TODO: ~ を解釈する
	if (commands == 0 || commands[1] == NULL)
	{
		puts("TODO: print usage");
		return ;
	}
	path = commands[1];

	if (chdir(path) < 0)
	{
		perror("chdir");
		return ;
	}

	char	buf[256];
	map_set(&g_env, "PWD", getcwd(buf, sizeof(buf)));
	// free
}