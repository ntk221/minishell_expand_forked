/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:22:25 by user              #+#    #+#             */
/*   Updated: 2023/02/17 22:34:29 by kazuki           ###   ########.fr       */
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
			return ;
		}
		else
			return ;
	}
	puts("TODO: print usage");
}