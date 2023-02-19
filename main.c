#include "minishell.h"

t_map	*g_env;

static void	readline_execpart(char *line)
{
	t_token		*tok;
	t_node		*node;

	tok = tokenizer(line);
	node = parse(tok);
	expand(node);
	exec(node);
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
