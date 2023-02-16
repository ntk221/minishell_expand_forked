/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:18:23 by user              #+#    #+#             */
/*   Updated: 2023/02/16 20:19:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_map	*g_env;

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