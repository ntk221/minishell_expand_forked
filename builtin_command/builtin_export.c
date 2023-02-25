/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:22:25 by user              #+#    #+#             */
/*   Updated: 2023/02/25 18:40:35 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ch_word_alphabet(unsigned char ch)
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

bool	exporterrorcheck(char **command, size_t *count)
{
	while (command[*count] != NULL && ft_strchr(command[*count], '=') == NULL)
	{
		if (exportwd_check(command[*count]) == false)
		{
			puts_errorstring_export(command[*count]);
			g_env->err_status = 1;
			return (false);
		}
		(*count)++;
	}
	if (command[*count] == NULL)
		return (true);
	if (exportwd_check(command[*count]) == false)
	{
		puts_errorstring_export(command[*count]);
		g_env->err_status = 1;
		return (false);
	}
	return (true);
}

void	show_sortedmap(void)
{
	return ;
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
		if (commands[command_position] == NULL)
			return (show_sortedmap());
		if (exporterrorcheck(commands, &command_position) == false || \
		commands[command_position] == NULL)
			return ;
		name_and_value = ft_split(commands[command_position], '=');
		if (!name_and_value)
			fatal_error("malloc");
		if (name_and_value[0] && name_and_value[1])
			map_set(&g_env, name_and_value[0], name_and_value[1]);
		free_commands(commands);
		free_commands(name_and_value);
	}
}
