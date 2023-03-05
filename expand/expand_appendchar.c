/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_appendchar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 01:03:13 by satushi           #+#    #+#             */
/*   Updated: 2023/03/05 17:16:41 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	append_char(char **s, char c)
{
	size_t	size;
	char	*new;

	size = 2;
	if (*s)
		size += ft_strlen(*s);
	new = malloc(size);
	if (new == NULL)
		fatal_error("malloc");
	if (*s)
		ft_strlcpy(new, *s, size);
	new[size - 2] = c;
	new[size - 1] = '\0';
	if (*s)
		free(*s);
	*s = new;
}

void	append_single(char **args, char **new)
{
	//bool	noaction;

	//noaction = true;
	while (**args != '\'')
	{
		//noaction = false;
		append_char(&(*new), **args);
		(*args)++;
	}
	//if (noaction == true)
		//*new = ft_strdup("");
	(*args)++;
}

static bool	slush_char_ch(char c)
{
	if (c == '$' || c == '"' || c == '\\')
		return (true);
	return (false);
}

void	append_double(char **args, char **new)
{
	//bool	noaction;

	//noaction = true;
	while (**args != '\"')
	{
		//noaction = false;
		if (**args == '\\' && slush_char_ch(*(*args + 1)) == true)
		{
			(*args)++;
			append_char(&(*new), **args);
			(*args)++;
		}
		else if (**args == '$' && *(*args + 1) != '\"')
			expand_doller_dq(&(*new), &(*args), *args);
		else
		{
			append_char(&(*new), **args);
			(*args)++;
		}
	}
	//if (noaction == true)
		//*new = ft_strdup("");
	(*args)++;
}
