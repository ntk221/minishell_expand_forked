/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 23:22:25 by user              #+#    #+#             */
/*   Updated: 2023/02/16 23:22:37 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	parse_redirect(t_redirect **redirect, t_token **tok)
{
	*redirect = malloc(sizeof(t_redirect));
	// error
	if (strcmp((*tok)->word, ">") == 0 && strcmp((*tok)->next->word, ">") == 0)
	{
		(*redirect)->type = APPEND;
		*tok = (*tok)->next;
	}
	else if (strcmp((*tok)->word, "<") == 0 && strcmp((*tok)->next->word, "<") == 0)
	{
		(*redirect)->type = HEREDOC;
		*tok = (*tok)->next;
	}
	else if (strcmp((*tok)->word, "<") == 0)
		(*redirect)->type = IN;
	else
		(*redirect)->type = OUT;

	// tok の next が word だったら redirect の filepathにそれを設定する
	if ((*tok)->next->kind == TK_WORD)
		(*redirect)->file_path = strdup((*tok)->next->word);
	else
		fatal_error("redirection end or not?\n");
	return true;
}