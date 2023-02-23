#include "minishell.h"

t_map	*g_env;

static void	readline_execpart(char *line)
{
	t_token		*tok;
	t_node		*node;
	t_node		*fnode;

	t_redirect	*redirect;
	t_token		*args_s;

	tok = tokenizer(line);
	node = parse(tok);
	fnode = node;
	while (node != NULL)
	{
		args_s = node->command->args;
		while (args_s != NULL)
		{
			printf("args is > %s\n", args_s->word);
			args_s = args_s->next;
		}
		if ((node->command->redirect) != NULL)
		{
			redirect = *node->command->redirect;
			while (redirect != NULL)
			{
				printf("file path is > %s\n", redirect->file_path);
				redirect = redirect->next;
			}
		}
		node = node->next;
	}
	expand(fnode);
	if (fnode->next == NULL && is_builtin(fnode->command->args->word))
	{
		redirect_reconect(fnode->command);
		g_env->err_status = do_builtin("test", fnode->command);
	}
	else
	{
		printf("check\n");
		g_env->err_status = exec(fnode);
	}
	if (tok != NULL)
		free_token(tok);
}

int main()
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
			break;
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
