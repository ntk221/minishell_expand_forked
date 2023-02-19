/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_wd_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satushi <satushi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 22:37:59 by user              #+#    #+#             */
/*   Updated: 2023/02/19 20:33:19 by satushi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	re_check(bool *flag, char **line, char *start)
{
	*flag = true;
	*line = start;
}

char	*ready_quotestring(char *start, bool *flag, char type)
{
	char	*append_line;

	append_line = NULL;
	append_line = ft_strjoin(append_line, token_append(SINGLE));
	while (strchr(append_line, type) == NULL)
		append_line = ft_strjoin(append_line, token_append(SINGLE));
	start = ft_strjoin(start, append_line);
	*flag = false;
}

t_token	*word(char **rest, char *line)
{
	char	*start;
	char	*returnword;
	bool	flag;

	start = line;
	flag = false;
	while (*line != '\0' && !is_metacharactert(*line) && !is_blank(*line))
	{
		if (*line == '\'')
		{
			line++;
			while (*line != '\'')
			{
				if (*line == '\0')
				{
					start = ready_quotestring(start, &flag, '\'');
					break ;
				}
				else
					line++;
			}
			line++;
			if (flag == false)
				re_check(&flag, &line, start);
		}
		else if (*line == '\"')
		{
			line++;
			while (*line != '\"')
			{
				if (*line == '\0')
				{
					start = ready_quotestring(start, &flag, '\'');
					break ;
				}
				else
					line++;
			}
			line++;
			if (flag == false)
				re_check(&flag, &line, start);
		}
		else
			line++;
	}
	returnword = strndup(start, line - start);
	if (returnword == NULL)
		fatal_error("strndup");
	*rest = line;
	return (new_token(returnword, TK_WORD));
}
