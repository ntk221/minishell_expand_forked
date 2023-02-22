/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:19:18 by user              #+#    #+#             */
/*   Updated: 2023/02/21 20:46:07 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ms_echo(char *line, t_command *command)
{
	char	**commands;
	size_t	position;

	(void)line;
	position = 1;
	commands = command_to_array(command);
	if (commands == NULL || commands[1] == NULL)
		return (0);
	if (strcmp(commands[position], "-n") == 0)
	{
		position++;
		while (commands[position] != NULL)
		{
			write(1, commands[position], ft_strlen(commands[position]));
			if (commands[position + 1] != NULL)
				write(1, " ", ft_strlen(" "));
			position++;
		}
	}
	else
	{
		while (commands[position] != NULL)
		{
			write(1, commands[position], ft_strlen(commands[position]));
			if (commands[position + 1] != NULL)
				write(1, " ", ft_strlen(" "));
			position++;
		}
		write(1, "\n", ft_strlen("\n"));
	}
	return (0);
}
