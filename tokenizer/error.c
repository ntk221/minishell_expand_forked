/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 21:56:53 by user              #+#    #+#             */
/*   Updated: 2023/02/16 21:57:36 by user             ###   ########.fr       */
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
	bool	syntax_error;

	syntax_error = true;
	dprintf(STDERR_FILENO, "Fatal Error: %s", location);
	while(*line)
		line++;
	*rest = line;
}
