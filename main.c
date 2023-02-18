#include "minishell.h"

t_map	*g_env;

// bool	is_builtin(char *line)
// {
// 	if (strncmp("export", line, ft_strlen("export")) == 0)
// 		return (true);
// 	else if (strncmp("env", line, ft_strlen("env")) == 0)
// 		return (true);
// 	else if (strncmp("pwd", line, ft_strlen("pwd")) == 0)
// 		return (true);
// 	else if (strncmp("cd", line, ft_strlen("cd")) == 0)
// 		return (true);
// 	else if (strncmp("exit", line, ft_strlen("exit")) == 0)
// 		return (true);
// 	else if (strncmp("unset", line, ft_strlen("unset")) == 0)
// 		return (true);
// 	else if (strncmp("echo", line, ft_strlen("echo")) == 0)
// 		return (true);
// 	else
//     	return (false);
// }

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
	extern char **environ;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	rl_outstream = stderr;
	env_init(&g_env, environ);
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break;
		if (*line != 0)
		{
			if (*line)
				add_history(line);
			// if (line[0] == '/' || line[0] == '.')
			//  	abusolute_path(line);
			readline_execpart(line);
		}
		free(line);
	}
	exit(0);
}
