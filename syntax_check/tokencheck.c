/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokencheck.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:01:14 by satushi           #+#    #+#             */
/*   Updated: 2023/02/25 18:09:20 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	wdcheck(char **str)
{
	char	type;
	char	*tmp_str;

	tmp_str = *str;
	if (strchr(*str, '\'') != NULL || strchr(*str, '\"') != NULL)
	{
		while (**str != '\'' && **str != '\"')
			(*str)++;
		type = **str;
		(*str)++;
		while (**str != type && **str != '\0')
			(*str)++;
		if (**str == '\0')
		{
			printf("bash: syntax error near quote `%s'\n", tmp_str);
			return (false);
		}
	}
	return (true);
}

bool	tokwdcheck(t_token *tok)
{
	char	*str;
	bool	tok_ok;

	tok_ok = true;
	while (tok != NULL && tok->kind != TK_EOF)
	{
		str = tok->word;
		while (*str != '\0')
		{
			if (false == wdcheck(&str))
				return (false);
			str++;
		}
		tok = tok->next;
	}
	return (true);
}
