/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:22:25 by user              #+#    #+#             */
/*   Updated: 2023/02/19 08:03:16 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_export(char *line, t_command *command)
{
	char	**commands;
	char	**name_and_value;

	(void)line;
	commands = command_to_array(command);
	if (commands != 0 && commands[0] != NULL)
	{
		name_and_value = ft_split(commands[1], '=');
		if (name_and_value[0] && name_and_value[1])
		{
			map_set(&g_env, name_and_value[0], name_and_value[1]);
			size_t i = 0;
			while(name_and_value[i])
			{
				free(name_and_value[i]);
				i++;
			}
			free(name_and_value);
			return ;
		}
		else
			return ;
	}
	free_commands(commands);
	puts("TODO: print usage");
}
