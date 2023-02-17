/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:20:06 by user              #+#    #+#             */
/*   Updated: 2023/02/17 22:34:23 by kazuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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