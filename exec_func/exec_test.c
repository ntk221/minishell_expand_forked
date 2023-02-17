/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satushi <satushi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 01:31:58 by satushi           #+#    #+#             */
/*   Updated: 2023/02/18 01:32:11 by satushi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
void    test_args_to_argv(void)
{
    char    *line = "cat";
    t_token *t = tokenizer(line);
    t_node  *n = parse(t);
    char    **argv = args_to_argv(n->command->args);
    for (int i = 0; argv[i] != NULL; i++)
        printf("%s\n", argv[i]);
    assert(argv[1] == NULL);
    interpret(n->command);
}

int main(void)
{
    //char    *line = "/bin/ls";

    //argv = line_to_argv(line);
    //for(int i = 0; argv[i] != NULL; i++)
    //    printf("%s\n", argv[i]);
    
    //line = "echo hoge";
    //t_token *t = tokenizer(line);
    //t_node  *n = parse(t);
    //for(t_token *itr = t; itr != NULL; itr = itr->next)
    //    printf("%s\n",itr->word);

    //printf("%s\n", n->command->args->word);
    //printf("%s\n", n->command->args->next->word);

    //char **argv = args_to_argv(n->command->args);
    //for (int i = 0; argv[i] != NULL; i++)
    //    printf("%s\n", argv[i]);
    //interpret(n->command);
    //interpret(argv[0], argv);
    test_args_to_argv();
}
*/