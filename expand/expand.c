/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 00:37:31 by satushi           #+#    #+#             */
/*   Updated: 2023/02/21 20:35:11 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	void	append_single(char **args, char **new)
{
	while (**args != '\'')
	{
		append_char(&(*new), **args);
		(*args)++;
	}
}

static	void	append_double(char **args, char **new, char *args_dummy)
{
	while (**args != '\"')
	{
		if (**args == '$')
			expand_doller_dq(&(*new), &(*args), args_dummy);
		else
		{
			append_char(&(*new), **args);
			(*args)++;
		}
	}
}

char	*expand_args(char *args, char *args_free)
{
	char	*new_word;

	new_word = NULL;
	while (*args != '\0')
	{
		if (*args == '\'' || *args == '\"')
		{
			args++;
			if (*(args - 1) == '\'')
				append_single(&args, &new_word);
			else if (*(args - 1) == '\"')
				append_double(&args, &new_word, args);
			args++;
		}
		else if (*args == '$' && *(args + 1) == '?')
			expand_dolleeques(&new_word, &args, args);
		else if (*args == '$')
			expand_doller(&new_word, &args, args);
		else
			append_char(&new_word, *args++);
	}
	free(args_free);
	return (new_word);
}

void	expand_redirect(t_redirect *redirect)
{
	while (redirect != NULL)
	{
		if (redirect->type != HEREDOC)
			redirect->file_path = expand_args(redirect->file_path, \
			redirect->file_path);
		redirect = redirect->next;
	}
}

// void	expand_doller(char **dst, char **rest, char *p)
// {
// 	char	*name;
// 	char	*value;

// 	name = calloc(1, sizeof(char));
// 	if (name == NULL)
// 		fatal_error("calloc");
// 	p++;
// 	if (!isalpha(*p) && *p != '_')
// 	{
// 		append_char(dst, *(p - 1));
// 		append_char(dst, *(p));
// 		*rest = p + 1;
// 		return ;
// 	}
// 	append_char(&name,*p++);
// 	while (isalpha(*p) != 0 || *p == '_' || isdigit(*p) != 0)
// 		append_char(&name,*p++);
// 	value = map_get(g_env, name);
// 	free(name);
// 	if (value)
// 		while (*value)
// 			append_char(dst, *value++);
// 	*rest = p;
// }

char	*expand_args_doller(char *args, char *args_free)
{
	char	*new_word;
	char	type;

	new_word = NULL;
	while (*args != '\0')
	{
		if (*args == '\'' || *args == '\"')
		{
			type = *args;
			append_char(&new_word, *args++);
			while (*args != type)
				append_char(&new_word, *args++);
			append_char(&new_word, *args++);
		}
		else if (*args == '$' && *(args + 1) == '?')
			expand_dolleeques(&new_word, &args, args);
		else if (*args == '$')
			expand_doller(&new_word, &args, args);
		else
			append_char(&new_word, *args++);
	}
	free(args_free);
	return (new_word);
}

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

void	split_tokenword(t_token *token, t_token **re_token)
{
	char	**tokenwd_split;
	size_t	position;

	tokenwd_split = ft_split(token->word, ' ');
	position = 0;
	while (tokenwd_split[position] != NULL)
	{
		(*re_token)->word = ft_strdup(tokenwd_split[position]);
		(*re_token)->kind = TK_WORD;
		if (tokenwd_split[position + 1] != NULL)
		{
			(*re_token)->next = (t_token *)malloc(sizeof(t_token) * 1);
			*re_token = (*re_token)->next;
		}
		free(tokenwd_split[position]);
		position++;
	}
	free(tokenwd_split);
}

void	remake_token(t_token *token, t_token *re_token)
{
	t_token	*tmp_token;

	while (token != NULL)
	{
		if (word_blankcheck(token->word))
			split_tokenword(token, &re_token);
		else
		{
			re_token->word = ft_strdup(token->word);
			re_token->kind = token->kind;
			if (token->next != NULL)
			{
				re_token->next = (t_token *)malloc(sizeof(t_token) * 1);
				re_token = re_token->next;
			}
		}
		tmp_token = token;
		token = token->next;
		free(tmp_token);
	}
	re_token->next = NULL;
}

void	expand_specialparam(t_token *token)
{
	char	*newword;

	newword = NULL;
	while (token != NULL)
	{
		token->word = expand_args_doller(token->word, token->word);
		token = token->next;
	}
}

char	*expand_args_quote(char *args, char *args_free)
{
	char	*new_word;

	new_word = NULL;
	while (*args != '\0')
	{
		if (*args == '\'' || *args == '\"')
		{
			args++;
			if (*(args - 1) == '\'')
				append_single(&args, &new_word);
			else if (*(args - 1) == '\"')
				append_double(&args, &new_word, args);
			args++;
		}
		else if (*args == '$' && *(args + 1) == '?')
			expand_dolleeques(&new_word, &args, args);
		else if (*args == '$')
			expand_doller(&new_word, &args, args);
		else
			append_char(&new_word, *args++);
	}
	free(args_free);
	return (new_word);
}

void	expand_quote(t_token *token)
{
	while (token != NULL)
	{
		token->word = expand_args_quote(token->word, token->word);
		token = token->next;
	}
}

t_token	*expand_simplecommand(t_token *token)
{
	t_token *re_token;
	t_token	*f_re_tok;

	re_token = (t_token *)malloc(sizeof(t_token) * 1);
	f_re_tok = re_token;
	expand_specialparam(token);
	remake_token(token, re_token);
	expand_quote(re_token);
	return (f_re_tok);
}

void	expand(t_node *node)
{
	t_redirect	*redirect;
	t_token		*token;

	while (node != NULL)
	{
		token = node->command->args;
		node->command->args = expand_simplecommand(token);
		if (node->command->redirect != NULL)
		{
			redirect = *(node->command->redirect);
			expand_redirect(redirect);
		}
		node = node->next;
	}
}
