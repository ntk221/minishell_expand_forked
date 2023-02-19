/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:19:18 by user              #+#    #+#             */
/*   Updated: 2023/02/19 08:09:09 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ms_echo(char *line, t_command *command)
{
	char	**commands;

	(void)line;
	commands = command_to_array(command);
	if (commands == NULL || commands[1] == NULL)
		return (0);
	if (strcmp(commands[1], "-n") == 0)
		write(1, commands[2], ft_strlen(commands[2]));
	else
	{
		write(1, commands[1], ft_strlen(commands[1]));
		write(1, "\n", ft_strlen("\n"));
	}
	size_t	i;

	i = 0;
	while (commands[i] != NULL)
	{
		free(commands[i]);
		i++;
	}
	free(commands);
	return (0);
}
