#include "../minishell.h"
#include <stdio.h>

t_map	*g_env;


/*void	shell_works(char *line)
{
	t_token	*tok;
	t_node	*node;

	tok = tokenizer(line);
	expand(tok);
	node = parse(tok);
	exec(&node);
	if (tok != NULL)
		free_token(tok);
	if (node != NULL)
		free_command_node(node);
}*/

void  sigint_handler()
{
  write(1, "\n", 1);
  rl_on_new_line();
  //rl_replace_line("", 0); 
  rl_redisplay(); 
}

#include <string.h>
char  *get_name(char *name_and_value)
{
	size_t	len;
	size_t	j;
	char	*name;

	len = 0;
	while(name_and_value[len] != '\0')
	{
		if (name_and_value[len] == '=')
			break;
		len++;
	}
	name = malloc(sizeof(char) * (len + 1));
	// error
	j = 0;
	while (len)
	{
		name[j] = name_and_value[j];
		j++;
		len--;
	}
	name[j] = '\0';
	return (name);
}

void	env_init(t_map **env, char **envp)
{
	size_t	i;
	char	*name;
	char	*value;

	i = 0;
	*env = malloc(sizeof(t_map));
	// error
	while (envp[i] != NULL)
	{
		name = get_name(envp[i]);
		value = getenv(name);
		map_set(env, name, value);
		i++;
	}
}

bool  is_builtin(char *line)
{
  char		*set[] = {"export", "env", "pwd", "cd", "exit", "unset", "echo", NULL};
  size_t	i;

  i = 0;
  while (set[i])
  {
	if (strncmp(set[i], line, ft_strlen(set[i])) == 0)
	{
		//puts("found!");
		return true;
	}
    i++;
  }
    return false;
}

void	ms_env(void)
{
	t_item	*itr;

	itr = g_env->item_head;
	while (itr != NULL)
	{
		size_t	size;
		char	*name_and_value;

		size = ft_strlen(itr->name) + ft_strlen(itr->value) + 2;
		name_and_value = malloc(size);
		strlcat(name_and_value, itr->name, size);
		strlcat(name_and_value, "=", size);
		strlcat(name_and_value, itr->value, size);
		printf("%s\n", name_and_value);
		free(name_and_value);
		itr = itr->next;
	}
}

char **command_to_array(t_command *command)
{
	char	**cmd_array;
	size_t	array_num;
	size_t	position;
	t_token	*args;

	array_num = 0;
	args = command->args;
	while (args != NULL && args->word != NULL)
	{
		array_num++;
		args = args->next;
	}
	cmd_array = (char **)malloc(sizeof(char *) * (array_num + 1));
	args = command->args;
	position = 0;
	while (position != array_num)
	{
		cmd_array[position] = ft_strdup(args->word);
		position++;
		args = args->next;
	}
	cmd_array[position] = NULL;
	return (cmd_array);
}

void	ms_export(char *line, t_command *command)
{
	char	**commands;
	char	**name_and_value;

	(void)line;
	commands = command_to_array(command);
	if (commands != 0 && commands[0] != NULL)
	{
		name_and_value = ft_split(commands[1], '=');
		printf("%s\n", name_and_value[0]);
		printf("%s\n", name_and_value[1]);
		if (name_and_value[0] && name_and_value[1])
		{
			printf("check\n");
			map_set(&g_env, name_and_value[0], name_and_value[1]);
			printf("check\n");
			return ;
		}
		else
			return ;
	}
	puts("TODO: print usage");
}

void	ms_pwd(void)
{
	printf("%s\n", map_get(g_env, "PWD"));
}

void	ms_cd(char *line, t_command *command)
{
	char	**commands;
	char	*path;

	commands = command_to_array(command);
	// TODO: ~ を解釈する
	if (commands == 0 || commands[1] == NULL)
	{
		puts("TODO: print usage");
		return ;
	}
	path = commands[1];

	if (chdir(path) < 0)
	{
		perror("chdir");
		return ;
	}

	char	buf[256];
	map_set(&g_env, "PWD", getcwd(buf, sizeof(buf)));
	// free
}

void	ms_exit(char *line)
{
	char	**commands;

	commands = ft_split(line, ' ');
	if (commands[1] == NULL)
	{
		printf("exit\n");
		exit(0);
	}
	if (!atoi(commands[1]) || (atoi(commands[1]) == -1 && ft_strlen(commands[1]) > 2))
	{
		printf("minishell: exit: numeric argument required\n");
		exit(255);
	}
	printf("exit\n");
	exit(atoi(commands[1]));
	
}

void	ms_unset(char *line)
{
	char	**commands;

	commands = ft_split(line, ' ');
	if (commands == NULL || commands[1] == NULL)
		return ;
	map_unset(&g_env, commands[1]);
}

void	ms_echo(char *line)
{
	char	**commands;

	commands = ft_split(line, ' ');
	if (commands == NULL || commands[1] == NULL)
		return ;
	if (strcmp(commands[1], "-n") == 0)
		ft_putstr_fd(commands[2], 1);
	else
		printf("%s\n", commands[1]);
}

void	do_builtin(char *line, t_command *command)
{
	if (strcmp(line, "env") == 0)
		ms_env();
	else if (strncmp(line, "export", 6) == 0)
		ms_export(line, command);
	else if (strcmp(line, "pwd") == 0)
		ms_pwd();
	else if (strncmp(line, "cd", 2) == 0)
		ms_cd(line, command);
	else if (strncmp(line, "exit", 4) == 0)
		ms_exit(line);
	else if (strncmp(line, "unset", 5) == 0)
		ms_unset(line);
	else if (strncmp(line, "echo", 4) == 0)
		ms_echo(line);
}

int main()
{
	char	  *line;
	t_token	*tok;
  	t_node  *node;
	//t_node	*fnode;
	extern char **environ;

	rl_outstream = stderr;
	env_init(&g_env, environ);
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break;
		if (*line)
			add_history(line);
		if (line[0] == '/' || line[0] == '.')
			abusolute_path(line);
		// else if (is_builtin(line))
		// 	do_builtin(line);
		else
		{
			tok = tokenizer(line);
			node = parse(tok);
			expand(node);
			if (is_builtin(node->command->args->word) && node->next == NULL)
				do_builtin(node->command->args->word, node->command);
			else
			{
				exec(node);
				if (tok != NULL)
					free_token(tok);
			}
		}
		free(line);
	}
	exit(0);
}