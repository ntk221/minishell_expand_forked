/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redirect_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satushi <satushi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 22:39:47 by user              #+#    #+#             */
/*   Updated: 2023/02/18 05:39:11 by satushi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*redirect(char **rest, char *line)
{
	static char *const	redirect[] = {"<", ">"};
	size_t				i;
	char				*re;

	i = 0;
	while (i < sizeof(redirect) / sizeof(*redirect))
	{
		if (startswith(line, redirect[i]))
		{
			re = strdup(redirect[i]);
			if (re == NULL)
				fatal_error("strdup");
			*rest = line + strlen(re);
			return (new_token(re, TK_REDIRECT));
		}
		i++;
	}
	fatal_error("Unexpected redirect");
}
