/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satushi <satushi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:59:30 by satushi           #+#    #+#             */
/*   Updated: 2023/02/23 20:00:57 by satushi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**args_to_argv(t_token *args)
{
	size_t	len;
	char	**argv;
	size_t	i;
	t_token	*itr;

	len = 0;
	i = 0;
	itr = args;
	while (itr != NULL)
	{
		len++;
		itr = itr->next;
	}
	argv = malloc(sizeof(char *) * (len + 1));
	itr = args;
	while (i != len)
	{
		argv[i] = ft_strdup(itr->word);
		itr = itr->next;
		i++;
	}
	argv[len] = NULL;
	return (argv);
}

int	stashfd(int fd)
{
	int	stashfd;

	stashfd = fcntl(fd, F_DUPFD, 10);
	if (stashfd < 0)
		fatal_error("fcntl");
	if (close(fd) < 0)
		fatal_error("close");
	return (stashfd);
}

char	*searchpath(const char *filename)
{
	char	*path;
	char	*value;
	char	*end;

	value = getenv("PATH");
	path = (char *)malloc(sizeof(char) * PATH_MAX);
	if (ft_strlen(filename) > PATH_MAX)
		fatal_error("strlen");
	while (*value != '\0')
	{
		bzero(path, PATH_MAX);
		end = ft_strchr(value, ':');
		if (end)
			strncpy(path, value, end - value);
		else
			ft_strlcpy(path, value, PATH_MAX);
		ft_strlcat(path, "/", PATH_MAX);
		ft_strlcat(path, filename, PATH_MAX);
		if (access(path, X_OK) == 0)
			return (accessok_file(path));
		if (end == NULL)
			return (NULL);
		value = end + 1;
	}
	return (NULL);
}

char	*accessok_file(char *path)
{
	char	*dup;

	dup = ft_strdup(path);
	if (dup == NULL)
		fatal_error("strdup");
	return (dup);
}
