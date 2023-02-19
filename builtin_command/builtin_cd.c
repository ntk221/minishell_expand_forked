/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:18:23 by user              #+#    #+#             */
/*   Updated: 2023/02/19 08:00:48 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_cd(char *line, t_command *command)
{
	char	**commands;
	char	*path;
	char	buf[256];

	(void)line;
	commands = command_to_array(command);
	if (!commands)
		perror("malloc");
	// TODO: ~ を解釈する
	if (commands[1] == NULL)
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
	map_set(&g_env, "PWD", getcwd(buf, sizeof(buf)));
	free_commands(commands);
}
