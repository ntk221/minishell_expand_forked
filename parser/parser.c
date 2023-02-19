/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satushi <satushi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 05:32:46 by satushi           #+#    #+#             */
/*   Updated: 2023/02/19 16:50:12 by satushi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	at_eof(t_token *tok)
{
	return (tok->kind == TK_EOF);
}

t_node	*new_node(t_node_kind kind)
{
	t_node	*node;

	node = calloc(1, sizeof(*node));
	if (node == NULL)
		fatal_error("calloc");
	node->kind = kind;
	node->command = calloc(1, sizeof(t_command));
	node->next = calloc(1, sizeof(node->next));
	node->command->redirect = NULL;
	return (node);
}

t_token	*tokdup(t_token *tok)
{
	char	*word;

	word = strdup(tok->word);
	if (word == NULL)
		fatal_error("strdup");
	return (new_token(word, tok->kind));
}

void	append_tok(t_token **tokens, t_token *tok)
{
	if (*tokens == NULL)
	{
		*tokens = tok;
		return ;
	}
	append_tok(&(*tokens)->next, tok);
}

void	ready_redirectinout(t_node *node)
{
	node->command->in_fd[0] = STDIN_FILENO;
	node->command->in_fd[1] = -1;
	node->command->out_fd[0] = -1;
	node->command->out_fd[1] = STDOUT_FILENO;
}

t_redirect	*tok_to_redirect(bool *flag, t_node *node, t_token *tok)
{
	parse_redirect(&(*node->command->redirect), &tok);
	*flag = false;
	(*node->command->redirect)->before = NULL;
	return (*node->command->redirect);
}

t_node	*parse(t_token *tok)
{
	t_node		*node;
	t_node		*fnode;
	t_redirect	*redirection_node;
	bool		first_action;

	node = new_node(ND_SIMPLE_CMD);
	fnode = node;
	node->command->redirect = (t_redirect **)malloc(sizeof(t_redirect *) * 1);
	ready_redirectinout(node);
	first_action = true;
	while (tok && !at_eof(tok))
	{
		if (tok->kind == TK_WORD)
		{
			parse_word(&node->command->args, tokdup(tok));
			tok = tok->next;
		}
		else if (tok->kind == TK_REDIRECT)
		{
			if (first_action == true)
				redirection_node = tok_to_redirect(&first_action, node, tok);
			else
			{
				parse_redirect(&redirection_node->next, &tok);
				redirection_node->next->before = redirection_node;
				redirection_node = redirection_node->next;
			}
			tok = tok->next->next;
		}
		else if (tok->kind == TK_OP)
		{
			if (first_action == true)
				(*(node->command->redirect)) = NULL;
			node->next = new_node(ND_SIMPLE_CMD);
			node = node->next;
			ready_redirectinout(node);
			node->command->redirect = \
			(t_redirect **)malloc(sizeof(t_redirect *) * 1);
			first_action = true;
			tok = tok->next;
		}
		else
			fatal_error("Implement parser");
	}
	if (first_action == true)
		(*(node->command->redirect)) = NULL;
	else
		redirection_node->next = NULL;
	node->next = NULL;
	return (fnode);
}
