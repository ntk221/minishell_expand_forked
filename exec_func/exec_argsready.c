/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_argsready.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satushi <satushi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:00:35 by satushi           #+#    #+#             */
/*   Updated: 2023/02/18 05:12:47 by satushi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**args_to_argv(t_token *args)
{
	size_t	len;
	char	**argv;
	size_t	i;

	len = 0;
	i = 0;
	for (t_token *itr = args; itr != NULL; itr = itr->next)
		len++;
	argv = malloc(sizeof(char *) * (len + 1));
	for (t_token *itr = args; i != len; itr = itr->next)
	{
		argv[i] = strdup(itr->word);
		i++;
	}
	argv[len] = NULL;
	return (argv);
}
