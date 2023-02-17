/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satushi <satushi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 01:39:08 by satushi           #+#    #+#             */
/*   Updated: 2023/02/18 02:11:19 by satushi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *searchpath(const char *filename)
{
    char path[PATH_MAX];
    char *value;
    char *end;

    value = getenv("PATH");
    if (strlen(filename) > PATH_MAX)
        fatal_error("strlen");
    while (*value != '\0')
    {
        bzero(path, PATH_MAX);
        end = strchr(value, ':');
        if (end)
            strncpy(path, value, end - value);
        else
            ft_strlcpy(path, value, PATH_MAX);
        ft_strlcat(path, "/", PATH_MAX);
        ft_strlcat(path, filename, PATH_MAX);
        if (access(path, X_OK) == 0)
        {
            char *dup;

            dup = strdup(path);
            if (dup == NULL)
                fatal_error("strdup");
            return (dup);
        }
        if (end == NULL)
            return (NULL);
        value = end + 1;
    }
    return (NULL);
}

int    stashfd(int fd)
{
    int    stashfd;

    stashfd = fcntl(fd, F_DUPFD, 10);
    if (stashfd < 0)
        fatal_error("fcntl");
    if (close(fd) < 0)
        fatal_error("close");
    return (stashfd);
}

pid_t exec_pipeline(t_node *node)
{
    extern char **environ;
    char        *path;
    pid_t       pid;
    char        **argv;

    if (node == NULL)
        return (-1);
    prepare_pipe(node);
    pid = fork();
    if (pid < 0)
		fatal_error("fork");
    else if (pid == 0)//childprocess
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        prepare_pipe_child(node);
        redirect_reconect(node->command);
        if (is_builtin(node->command->args->word))
            exit(do_builtin(node->command->args->word, node->command));
        else
        {
            argv = args_to_argv(node->command->args);
            path = argv[0];
            execve(searchpath(path), argv, environ);
            fatal_error("excve");
        }
    }
    else
    {
        prepare_pipe_parent(node);//ここから親プロセス    
        if (node->next)
            return (exec_pipeline(node->next));
    }
    return (pid);
}

int exec(t_node *node)
{
    pid_t   last_pid;
    int     status;

    ready_redirectionfile(node);
    last_pid = exec_pipeline(node);
    status = wait_pipeline(last_pid);
    return (status);
}

