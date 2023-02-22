/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 08:22:33 by marvin            #+#    #+#             */
/*   Updated: 2023/02/22 08:22:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char    *open_redirectspecialparam()
// {

// }

void	check_doller(char **rest, char *p, t_redirect *redirect)
{
	char	*name;
	char	*value;

	name = calloc(1, sizeof(char));
	if (name == NULL)
		fatal_error("calloc");
	p++;
	if (!isalpha(*p) && *p != '_')
	{
		*rest = p + 1;
        free(name);
		return ;
	}
	append_char(&name,*p++);
	while (isalpha(*p) != 0 || *p == '_' || isdigit(*p) != 0)
		append_char(&name,*p++);
	value = map_get(g_env, name);
	free(name);
	if (value == NULL || strchr(value, ' ') != NULL)
		redirect->ambigous = true;
    else
		redirect->ambigous = false;
	*rest = p;
}

void    specialparam_check(t_redirect *redirect)
{
    char    *args;
    char    type;

    while (redirect != NULL)
    {
        args = redirect->file_path;
        printf("filepath is > %s\n", redirect->file_path);
        while (*args != '\0')
        {
            if (*args == '\'' || *args == '\"')
            {
                type = *args;
                args++;
                while (*args != type)
                    args++;
                args++;
            }
            else if (*args == '$' && *(args + 1) == '?')
                args = args + 2;
            else if (*args == '$')
                check_doller(&args, args, redirect);
            else
                args++;
        }
		printf("ambigous is > %d\n", redirect->ambigous);
        redirect = redirect->next;
    }
}

t_redirect	*expand_redirect_ten(t_redirect *redirect)
{
	//t_redirect	*f_redirect;

	specialparam_check(redirect);
	return NULL;
	//remake_token(token, re_token);
	//expand_quote(re_token);
	//return (f_re_tok);
}