/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 22:20:25 by user              #+#    #+#             */
/*   Updated: 2023/02/16 22:21:14 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
testcode space
*/

/*void	test_tokenizer(void)
{
	char	*line = "echo hoge | echo huga";
	t_token *t = tokenizer(line);
	t_token *itr = t;
	while(itr->next != NULL)
	{
		printf("%s\n", itr->word);
		itr = itr->next;
	}
	free_token(t);	
	line = "echo\thoge";
	t = tokenizer(line);
	itr = t;
	while(itr->next != NULL)
	{
		printf("%s\n", itr->word);
		itr = itr->next;
	}
	free_token(t);
	line = "echo < hoge";
	t = tokenizer(line);
	itr = t;
	while(itr->next != NULL)
	{
		printf("%s\n", itr->word);
		itr = itr->next;
	}
	free_token(t);

	line = "< in cat";
	t = tokenizer(line);
	itr = t;
	while(itr->next != NULL)
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
}

int	main(void)
{
	test_tokenizer();
}
*/