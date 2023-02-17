/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_doller.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satushi <satushi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 01:04:15 by satushi           #+#    #+#             */
/*   Updated: 2023/02/18 01:04:34 by satushi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_doller(char **dst, char **rest, char *p)
{
	char    *name;
    char    *value;

    name = calloc(1, sizeof(char));
    if (name == NULL)
        fatal_error("calloc");
    if (*p != '$')
        fatal_error("Expected dollar sign");
    p++;
    if (!isalpha(*p) && *p != '_')
        fatal_error("Variable must starts with alphabetic character or underscore.");
    append_char(&name,*p++);
    while (isalpha(*p) != 0 || *p == '_' || isdigit(*p) != 0)
        append_char(&name,*p++);
    value = map_get(g_env, name);
    free(name);
    if (value)
        while (*value)
            append_char(dst, *value++);
    *rest = p;
}

void	expand_doller_dq(char **dst, char **rest, char *p)
{
	char    *name;
    char    *value;

    name = calloc(1, sizeof(char));
    if (name == NULL)
        fatal_error("calloc");
    if (*p != '$')
        fatal_error("Expected dollar sign");
    p++;
    if (!isalpha(*p) && *p != '_')
        fatal_error("Variable must starts with alphabetic character or underscore.");
    append_char(&name,*p++);
    while ((isalpha(*p) != 0 || *p == '_' || isdigit(*p) != 0) && *p != '\"')
        append_char(&name,*p++);
    value = getenv(name);
    free(name);
    if (value)
        while (*value)
            append_char(dst, *value++);
    *rest = p;
}