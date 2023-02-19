/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satushi <satushi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 00:37:31 by satushi           #+#    #+#             */
/*   Updated: 2023/02/19 14:37:49 by satushi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static	void	expand_args_in_quote(char **args, char *new_word, char type)
// {
// 	*args++;
// 	if (type == "\'")
// 		while (**args != '\'')
// 			append_char(&new_word, **args++);
// 	else if (type == '\"')
// 	{
// 		while (**args != '\"')
// 		{
// 			if (*args == '$')
// 				expand_doller_dq(&new_word, args, *args);
// 			else
// 				append_char(&new_word, **args++);
// 		}
// 	}
// 	*args++;
// }

char	*expand_args(char *args, char *args_free)
{
	char	*new_word;

	new_word = NULL;
	while (*args != '\0')
	{
		// if (*args == '\'')
		// {
		// 	args++;
		// 	while (*args != '\'')
		// 		append_char(&new_word, *args++);
		// 	args++;
		// }
		// else if (*args == '\"')
		// {
		// 	args++;
		// 	while (*args != '\"')
		// 	{
		// 		if (*args == '$')
		// 			expand_doller_dq(&new_word, &args, args);
		// 		else
		// 			append_char(&new_word, *args++);
		// 	}
		// 	args++;
		// }
		if (*args == '\'' || *args == '\"')
		{
			args++;
			if (*args == '\'')
				while (*args != '\'')
					append_char(&new_word, *args++);
			else if (*args == '\"')
			{
				if (*args == '$')
					expand_doller_dq(&new_word, &args, args);
				else
					append_char(&new_word, *args++);
			}
			args++;
		}
		else if (*args == '$')
			expand_doller(&new_word, &args, args);
		else
			append_char(&new_word, *args++);
	}
	free(args_free);
	return (new_word);
}

void	expand(t_node *node)
{
	t_redirect	*redirect;
	t_token		*token;

	while (node != NULL)
	{
		token = node->command->args;
		while (token != NULL)
		{
			token->word = expand_args(token->word, token->word);
			token = token->next;
		}
		if (node->command->redirect != NULL)
		{
			redirect = *(node->command->redirect);
			while (redirect != NULL)
			{
				if (redirect->type != HEREDOC)
					redirect->file_path = expand_args(redirect->file_path, \
					redirect->file_path);
				redirect = redirect->next;
			}
		}
		node = node->next;
	}
}
