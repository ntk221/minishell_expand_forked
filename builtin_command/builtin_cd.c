/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satushi <satushi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:18:23 by user              #+#    #+#             */
/*   Updated: 2023/02/23 17:28:38 by satushi          ###   ########.fr       */
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
		fatal_error("malloc");
	if (commands[1] == NULL || commands[2] != NULL)
	{
		free_commands(commands);
		puts("TODO: print usage");
		return ;
	}
	path = commands[1];
	if (chdir(path) < 0 || getcwd(NULL, 0) == NULL)
	{
		perror("chdir");
		free_commands(commands);
		return ;
	}
	map_set(&g_env, "PWD", getcwd(buf, sizeof(buf)));
	free_commands(commands);
}
