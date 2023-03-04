/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokencheck.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:01:14 by satushi           #+#    #+#             */
/*   Updated: 2023/03/04 21:23:52 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	only_twowd(char	*str)
{
	if (*str == '\\' && (*(str + 1) == '\"' || \
	*(str + 1) == '\'') && *(str + 2) == '\0')
		return (true);
	return (false);
}

bool	wdcheck(char **str)
{
	char	type;
	char	*tmp_str;

	tmp_str = *str;
	if (ft_strchr(*str, '\'') != NULL || ft_strchr(*str, '\"') != NULL)
	{
		while (**str != '\'' && **str != '\"')
			(*str)++;
		type = **str;
		(*str)++;
		while (**str != type && **str != '\0')
		{
			if (**str == '\\')
				(*str)++;
			(*str)++;
		}
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

	while (tok != NULL && tok->kind != TK_EOF)
	{
		str = tok->word;
		if (only_twowd(str) != true)
		{
			while (*str != '\0')
			{
				if (false == wdcheck(&str))
					return (false);
				str++;
			}
		}
		tok = tok->next;
	}
	return (true);
}
