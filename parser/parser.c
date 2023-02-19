/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satushi <satushi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 05:32:46 by satushi           #+#    #+#             */
/*   Updated: 2023/02/19 19:33:55 by satushi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	ready_redirectinout(t_node *node, bool *flag, bool f_content)
// {
// 	if (f_content == true)
// 		node->command->redirect = (t_redirect **)malloc(sizeof(t_redirect *) * 1);
// 	node->command->in_fd[0] = STDIN_FILENO;
// 	node->command->in_fd[1] = -1;
// 	node->command->out_fd[0] = -1;
// 	node->command->out_fd[1] = STDOUT_FILENO;
// 	*flag = true;
// }

t_node *ready_nextnode(bool *flag, t_node *node, t_token **token)
{
	if (*flag == true)
		(*(node->command->redirect)) = NULL;
	node->next = new_node(ND_SIMPLE_CMD);
	ready_redirectinout(node->next, &(*flag), false);
	node->next->command->redirect = (t_redirect **)malloc(sizeof(t_redirect *) * 1);
	*token = (*token)->next;
	return (node->next);
}

void	tok_parsing(t_token *tok, t_node *node, bool first_action)
{
	t_redirect *redirection_node;

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
}

t_node	*parse(t_token *tok)
{
	t_node		*node;
	t_node		*fnode;
	bool		first_action;

	node = new_node(ND_SIMPLE_CMD);
	fnode = node;
	ready_redirectinout(node, &first_action, true);
	tok_parsing(tok, node, first_action);
	return (fnode);
}
