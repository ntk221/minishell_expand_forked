/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satushi <satushi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 05:32:46 by satushi           #+#    #+#             */
/*   Updated: 2023/02/19 17:30:36 by satushi          ###   ########.fr       */
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

void	ready_redirectinout(t_node *node, bool *flag)
{
	node->command->in_fd[0] = STDIN_FILENO;
	node->command->in_fd[1] = -1;
	node->command->out_fd[0] = -1;
	node->command->out_fd[1] = STDOUT_FILENO;
	*flag = true;
}

t_redirect	*tok_to_redirect_f(bool *flag, t_node *node, t_token *tok)
{
	parse_redirect(&(*node->command->redirect), &tok);
	*flag = false;
	(*node->command->redirect)->before = NULL;
	return (*node->command->redirect);
}

t_redirect	*tok_to_redirect(t_redirect *redirect, t_token *tok)
{
	parse_redirect(&redirect->next, &tok);
	redirect->next->before = redirect;
	return (redirect->next);
}

t_node *ready_nextnode(bool *flag, t_node *node, t_token **token)
{
	if (*flag == true)
		(*(node->command->redirect)) = NULL;
	node->next = new_node(ND_SIMPLE_CMD);
	ready_redirectinout(node->next, &flag);
	node->next->command->redirect = (t_redirect **)malloc(sizeof(t_redirect *) * 1);
	*token = (*token)->next;
	return (node->next);
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
	ready_redirectinout(node, &first_action);
	//first_action = true;
	while (tok && !at_eof(tok))
	{
		if (tok->kind == TK_WORD)
			tok = parse_word(&node->command->args, tokdup(tok), tok);
		else if (tok->kind == TK_REDIRECT)
		{
			if (first_action == true)
				redirection_node = tok_to_redirect_f(&first_action, node, tok);
			else
				redirection_node = tok_to_redirect(redirection_node, tok);
			tok = tok->next->next;
		}
		else if (tok->kind == TK_OP)
			node = ready_nextnode(&first_action, node, &tok);
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
