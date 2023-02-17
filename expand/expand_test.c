/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satushi <satushi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 00:39:25 by satushi           #+#    #+#             */
/*   Updated: 2023/02/18 00:39:28 by satushi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



/*#include <stdio.h>
int main(void)
{
	char 	*line = "\"echo hoge\"";
	t_token	*t = tokenizer(line);
	quote_removal(t);
	free_token(t);
	line = "\'echo\thoge\'";
	t = tokenizer(line);
	quote_removal(t);
	t_token *itr = t;
	while (itr->next != NULL)
	{
		printf("%s\n", itr->word);
		itr = itr->next;
	}
	free_token(t);
}

__attribute__((destructor))
static void destructor()
{
	system("leaks -q a.out");
}*/