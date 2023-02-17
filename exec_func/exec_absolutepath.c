/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_absolutepath.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satushi <satushi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 01:56:43 by satushi           #+#    #+#             */
/*   Updated: 2023/02/18 01:57:47 by satushi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int abusolute_path(char *line)
{
    char    **argv;
    pid_t pid;
	int wstatus;
	extern char **environ;

    pid = fork();
    if (pid < 0)
        fatal_error("fork");
    else if (pid == 0)
    {
        argv = line_to_argv(line);
        execve(argv[0], argv, environ);
        fatal_error("execve\n");
        return (1);
    }
    else
    {
        wait(&wstatus);
        return (WEXITSTATUS(wstatus));
    }
}
