/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simplecommand_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 20:32:36 by marvin            #+#    #+#             */
/*   Updated: 2023/02/26 20:32:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	word_blankcheck(char *string)
{
	while (*string != '\0')
	{
		if (is_blank(*string))
			return (true);
		string++;
	}
	return (false);
}

void	re_token_in_null(t_token **token, t_token **re_token)
{
	(*re_token)->word = NULL;
	(*re_token)->kind = TK_WORD;
	if ((*token)->next != NULL)
	{
		(*re_token)->next = (t_token *)malloc(sizeof(t_token) * 1);
		(*re_token) = (*re_token)->next;
	}
	(*token) = (*token)->next;
}

void	re_token_make(t_token **retoken, t_token *token)
{
	(*retoken)->word = ft_strdup(token->word);
	(*retoken)->kind = token->kind;
	if (token->next != NULL)
	{
		(*retoken)->next = (t_token *)malloc(sizeof(t_token) * 1);
		(*retoken) = (*retoken)->next;
	}
}

void	remake_token(t_token *token, t_token *re_token)
{
	t_token	*head;

	head = token;
	while (token != NULL)
	{
		if (token->word == NULL && (token->next == NULL \
		|| token->next->kind == TK_OP))
			re_token_in_null(&token, &re_token);
		else if (token->word == NULL)
			token = token->next;
		else if (word_blankcheck(token->word) && \
		(ft_strchr(token->word, '\'') == NULL && ft_strchr(token->word, '\"') == NULL)) //token->word[0] != '\'' && token->word[0] != '\"'
			split_tokenword(&token, &re_token);
		else
		{
			re_token_make(&re_token, token);
			token = token->next;
		}
	}
	free_token(head);
	re_token->next = NULL;
}
