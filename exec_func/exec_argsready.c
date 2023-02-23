/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_argsready.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satushi <satushi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:00:35 by satushi           #+#    #+#             */
/*   Updated: 2023/02/23 20:02:13 by satushi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char	**args_to_argv(t_token *args)
// {
// 	size_t	len;
// 	char	**argv;
// 	size_t	i;
// 	t_token	*itr;

// 	len = 0;
// 	i = 0;
// 	itr = args;
// 	while (itr != NULL)
// 	{
// 		len++;
// 		itr = itr->next;
// 	}
// 	argv = malloc(sizeof(char *) * (len + 1));
// 	itr = args;
// 	while (i != len)
// 	{
// 		argv[i] = ft_strdup(itr->word);
// 		itr = itr->next;
// 		i++;
// 	}
// 	argv[len] = NULL;
// 	return (argv);
// }
