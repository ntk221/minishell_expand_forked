/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satushi <satushi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:19:18 by user              #+#    #+#             */
/*   Updated: 2023/02/18 02:22:26 by satushi          ###   ########.fr       */
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
	return (0);
}
