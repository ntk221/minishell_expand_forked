/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:22:25 by user              #+#    #+#             */
/*   Updated: 2023/03/02 12:39:27 by marvin           ###   ########.fr       */
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
		if (!isascii(*arg))
			return (false);
		arg++;
	}
	return (true);
}

void	map_insert(char *s, char *e, char *l)
{
	char		*set1;
	char		*set2;
	long int	position;

	position = 0;
	set1 = (char *)malloc(sizeof(char) * (e - s + 1));
	while (position != (e - s))
	{
		set1[position] = s[position];
		position++;
	}
	set1[position] = '\0';
	if (l == e)
		set2 = ft_strdup("\0");
	else
	{
		position = e - s + 1;
		set2 = (char *)malloc(sizeof(char) * (l - e));
		while (s[position] != '\0')
		{
			set2[position - (e - s + 1)] = s[position];
			position++;
		}
		set2[position - (e - s + 1)] = '\0';
	}
	map_set(&g_env, set1, set2);
	free(set1);
	free(set2);
}

void	exporterrorcheck(char **command)
{
	char	*start;
	char	*end;
	char	*equal;
	size_t	count;

	count = 1;
	while (command[count] != NULL)
	{
		if (exportwd_check(command[count]) == false)
			puts_errorstring_export(command[count]);
		if (ft_strchr(command[count], '=') != NULL)
		{
			start = command[count];
			equal = start;
			end = command[count] + ft_strlen(command[count]);
			while (*equal != '=')
				equal++;
			map_insert(start, equal, end);
		}
		(count)++;
	}
}

void	ms_export(char *line, t_command *command)
{
	char	**commands;

	(void)line;
	commands = command_to_array(command);
	if (!commands)
		fatal_error("malloc");
	if (commands[0] != NULL)
	{
		if (commands[1] == NULL)
			return (show_sortedmap());
		exporterrorcheck(commands);
		free_commands(commands);
	}
}
