/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:43:24 by mochitteiun       #+#    #+#             */
/*   Updated: 2023/03/03 19:43:24 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	sp_wd_ch(char c)
{
	if (c == '"' || c == '$' || c == '\\')
		return (true);
	return (false);
}

void	export_argsremake(t_token *token)
{
	char	*sub;
	char	*free_sub;
	char	*dup;

	while (token != NULL)
	{
		dup = NULL;
		sub = token->word;
		free_sub = sub;
		while (*sub != '\0')
		{
			if (*sub == '\\' && sp_wd_ch(*(sub + 1)) == true)
				append_char(&dup, *sub++);
			else if (*(sub - 1) != '\\' && sp_wd_ch(*sub) == true)
				append_char(&dup, '\\');
			append_char(&dup, *sub);
			sub++;
		}
		token->word = dup;
		free(free_sub);
		token = token->next;
	}
}

void	append_double_export(char **args, char **new)
{
	bool	noaction;

	noaction = true;
	while (**args != '\"')
	{
		noaction = false;
		if (**args == '$' && *(*args + 1) != '\"')
			expand_doller_dq(&(*new), &(*args), *args);
		else
		{
			if (**args == '\\')
			{
				append_char(&(*new), **args);
				(*args)++;
			}
			append_char(&(*new), **args);
			(*args)++;
		}
	}
	if (noaction == true)
		*new = ft_strdup("");
	(*args)++;
}

char	*expand_args_expote(char *args, char *args_free)
{
	char	*new_word;

	new_word = NULL;
	while (*args != '\0')
	{
		if (*args == '\\')
		{
			append_char(&new_word, *args++);
			append_char(&new_word, *args++);
		}
		else if ((*args == '\'' || *args == '\"') && *(args + 1) != '\0')
		{
			args++;
			if (*(args - 1) == '\'')
				append_single(&args, &new_word);
			else if (*(args - 1) == '\"')
				append_double_export(&args, &new_word);
		}
		else if (*args == '$' && (*(args + 1) == '\0' || \
		*(args + 1) == '\'' || *(args + 1) == '\"'))
			append_char(&new_word, *args++);
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

void	expand_export(t_token *token)
{
	while (token != NULL)
	{
		if (token->word != NULL)
			token->word = expand_args_expote(token->word, token->word);
		token = token->next;
	}
}
