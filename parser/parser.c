/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 05:32:46 by satushi           #+#    #+#             */
/*   Updated: 2023/02/19 07:14:10 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**************************************************
 * 
 *	SHELL GRAMMER
 * .  Simple Commands 
 * 		A simple command is a sequence of optional variable 
 * 		assignments followed by blank-separated words and redirections,
 * 		and terminated by a control operator(パイプとか?).
 * 
 *************************************************/

#include "../minishell.h"

t_token	*new_token(char *word, t_token_kind kind);

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
	node->next = NULL;
	node->command->redirect = NULL;
	return (node);
}

void	free_redirect(t_redirect *redirect);

void	free_node(t_node *node)
{
	t_node	*itr;
	t_node	*next;

	itr = node;
	while (itr != NULL)
	{
		if(itr->command->redirect != NULL)
			free_redirect(itr->command->redirect);
		free_token(itr->command->args);
		free(itr->command);
		next = itr->next;
		free(itr);
		itr = next;
	}
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

bool	parse_redirect(t_redirect **redirect, t_token **tok);

t_node	*parse(t_token *tok)
{
	t_node		*node;
	t_node		*first_node;
	t_redirect	*itr;
	bool		first_action;

	node = new_node(ND_SIMPLE_CMD);
	first_node = node;
	// node->command->redirect = (t_redirect *)malloc(sizeof(t_redirect *) * 1);
	node->command->in_fd[0] = STDIN_FILENO;
	node->command->in_fd[1] = -1;
	node->command->out_fd[0] = -1;
	node->command->out_fd[1] = STDOUT_FILENO;
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
			{
				parse_redirect(&(node->command->redirect), &tok);
				first_action = false;
				node->command->redirect->before = NULL;
				itr = node->command->redirect;
			}
			else
			{
				parse_redirect(&itr->next, &tok);
				itr->next->before = itr;
				itr = itr->next;
			}
			tok = tok->next->next;
		}
		else if (tok->kind == TK_OP)
		{
			if (first_action == true)
				node->command->redirect = NULL;
			node->next = new_node(ND_SIMPLE_CMD);
			node = node->next;
			node->command->in_fd[0] = STDIN_FILENO;
			node->command->in_fd[1] = -1;
			node->command->out_fd[0] = -1;
			node->command->out_fd[1] = STDOUT_FILENO;
			node->command->redirect = \
			(t_redirect *)malloc(sizeof(t_redirect *) * 1);
			first_action = true;
			tok = tok->next;
		}
		else
			fatal_error("Implement parser");
	}
	if (first_action == true)
	{
		free(node->command->redirect);
		node->command->redirect = NULL;
	}
	else
		itr->next = NULL;
	node->next = NULL;
	return (first_node);
}
