/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_doller.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 01:04:15 by satushi           #+#    #+#             */
/*   Updated: 2023/02/21 11:33:14 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_doller(char **dst, char **rest, char *p)
{
	char	*name;
	char	*value;

	name = calloc(1, sizeof(char));
	if (name == NULL)
		fatal_error("calloc");
	p++;
	if (!isalpha(*p) && *p != '_')
	{
		append_char(dst, *(p - 1));
		append_char(dst, *(p));
		*rest = p + 1;
		return ;
	}
	append_char(&name,*p++);
	while (isalpha(*p) != 0 || *p == '_' || isdigit(*p) != 0)
		append_char(&name,*p++);
	value = map_get(g_env, name);
	free(name);
	if (value)
		while (*value)
			append_char(dst, *value++);
	*rest = p;
}

void	expand_doller_dq(char **dst, char **rest, char *p)
{
	char	*name;
	char	*value;

	name = calloc(1, sizeof(char));
	if (name == NULL)
		fatal_error("calloc");
	p++;
	if (!isalpha(*p) && *p != '_')
	{
		append_char(dst, *(p - 1));
		append_char(dst, *(p));
		*rest = p + 1;
		return ;
	}
	append_char(&name,*p++);
	while ((isalpha(*p) != 0 || *p == '_' || isdigit(*p) != 0) && *p != '\"')
		append_char(&name,*p++);
	value = getenv(name);
	free(name);
	if (value)
		while (*value)
			append_char(dst, *value++);
	*rest = p;
}
