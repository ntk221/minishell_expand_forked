/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satushi <satushi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:22:25 by user              #+#    #+#             */
/*   Updated: 2023/02/25 17:42:39 by satushi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ch_word_alphabet(char ch)
{
	if ((('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z')) || ch == '_')
		return (true);
	return (false);
}

bool	exportwd_check(char *arg)
{
	if (ch_word_alphabet(*arg) == false)
		return (false);
	arg++;
	while (*arg != '\0' && *arg != '=')
	{
		if (!(0 <= *arg && *arg <= 127))
			return (false);
		arg++;
	}
	return (true);
}

void	ms_export(char *line, t_command *command)
{
	char	**commands;
	char	**name_and_value;
	size_t	command_position;

	(void)line;
	command_position = 1;
	commands = command_to_array(command);
	if (!commands)
		fatal_error("malloc");
	if (commands[0] != NULL)
	{
		if (commands[1] == NULL)
		{
			printf("output\n");
			return ;
		}
		while (commands[command_position] != NULL && ft_strchr(commands[command_position], '=') == NULL)
		{
			if (exportwd_check(commands[command_position]) == false)
			{
				printf("minishell: export: `%s': not a valid identifier\n", commands[command_position]);
				return ;
			}
			command_position++;
		}
		if (commands[command_position] == NULL)
			return ;
		if (exportwd_check(commands[command_position]) == false)
		{
			printf("minishell: export: `%s': not a valid identifier\n", commands[command_position]);
			return ;
		}
		name_and_value = ft_split(commands[command_position], '=');
		if (!name_and_value)
			fatal_error("malloc");
		if (name_and_value[0] && name_and_value[1])
		{
			map_set(&g_env, name_and_value[0], name_and_value[1]);
			free_commands(commands);
			free_commands(name_and_value);
			return ;
		}
		else
		{
			free_commands(commands);
			free_commands(name_and_value);
			return ;
		}
	}
}
