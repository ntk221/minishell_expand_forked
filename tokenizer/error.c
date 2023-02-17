/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satushi <satushi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 21:56:53 by user              #+#    #+#             */
/*   Updated: 2023/02/18 05:41:30 by satushi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fatal_error(const char *msg)
{
	dprintf(STDERR_FILENO, "Fatal Error: %s", msg);
	exit(1);
}

void	tokenize_error(const char *location, char **rest, char *line)
{
	dprintf(STDERR_FILENO, "Fatal Error: %s", location);
	while (*line)
		line++;
	*rest = line;
}
