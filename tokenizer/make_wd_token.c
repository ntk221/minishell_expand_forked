/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_wd_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 22:37:59 by user              #+#    #+#             */
/*   Updated: 2023/02/16 22:38:26 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token *word(char **rest, char *line)
{
    char *start;
    char *returnword;
	char *append_line;
	bool flag;

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
					append_line = NULL;
					append_line = ft_strjoin(append_line, token_append(SINGLE));
					while (strchr(append_line, '\'') == NULL)
						append_line = ft_strjoin(append_line, token_append(SINGLE));
					start = ft_strjoin(start, append_line);
					flag = false;
					break;
				}
				else
					line++;
			}
			line++;
			if (flag == false)
			{
				flag = true;
				line = start;
			}
		}
		else if (*line == '\"')
		{
			line++;
			while (*line != '\"')
			{
				if (*line == '\0')
				{
					append_line = NULL;
					append_line = ft_strjoin(append_line, token_append(DOUBLE));
					while (strchr(append_line, '\"') == NULL)
						append_line = ft_strjoin(append_line, token_append(DOUBLE));
					start = ft_strjoin(start, append_line);
					flag = false;
					break;
				}
				else
					line++;
			}
			line++;
			if (flag == false)
			{
				flag = true;
				line = start;
			}
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