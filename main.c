/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:27:43 by satushi           #+#    #+#             */
/*   Updated: 2023/02/24 13:08:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_map	*g_env;

static void	readline_execpart(char *line)
{
	t_token		*tok;
	t_node		*node;

	tok = tokenizer(line);
	if (tokcheck(tok) == false)
	{
		free_token(tok);
		return ;
	}
	node = parse(tok);
	expand(node);
	if (node->next == NULL && is_builtin(node->command->args->word))
	{
		ready_redirectionfile(node);
		exec_check(node, args_to_argv(node->command->args)[0]);
		if (redirect_reconect(node->command) == 1)
		{
			g_env->err_status = -1;
			return ;
		}
		g_env->err_status = do_builtin("test", node->command);
	}
	else
		g_env->err_status = exec(node);
	if (tok != NULL)
		free_token(tok);
}

int	main(void)
{
	char		*line;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	rl_outstream = stderr;
	env_init(&g_env);
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line != 0)
		{
			if (*line)
				add_history(line);
			readline_execpart(line);
		}
		free(line);
	}
	exit(0);
}

// /home/user/.local/bin/norminette
// /home/user/.local/lib/python3.10/site-packages/norminette