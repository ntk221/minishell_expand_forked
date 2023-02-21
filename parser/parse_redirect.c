/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satushi <satushi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 23:22:25 by user              #+#    #+#             */
/*   Updated: 2023/02/18 05:32:38 by satushi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	parse_redirect(t_redirect **redirect, t_token **tok)
{
	*redirect = malloc(sizeof(t_redirect)); // new_redirect
	if (strcmp((*tok)->word, ">") == 0 && strcmp((*tok)->next->word, ">") == 0)
	{
		(*redirect)->type = APPEND;
		*tok = (*tok)->next;
	}
	else if (strcmp((*tok)->word, "<") == 0 \
	&& strcmp((*tok)->next->word, "<") == 0)
	{
		(*redirect)->type = HEREDOC;
		*tok = (*tok)->next;
	}
	else if (strcmp((*tok)->word, "<") == 0)
		(*redirect)->type = IN;
	else
		(*redirect)->type = OUT;
	if ((*tok)->next->kind == TK_WORD)
		(*redirect)->file_path = strdup((*tok)->next->word);
	else
		fatal_error("redirection end or not?\n");
	return (true);
}

void	free_redirect(t_redirect *redirect)
{
	t_redirect	*next;

	if (redirect == NULL)
		return ;
	next = redirect->next;
	if (redirect->file_path != NULL)
		free(redirect->file_path);
	free(redirect);
	free_redirect(next);
}