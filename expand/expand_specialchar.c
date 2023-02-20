/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_specialchar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 21:08:20 by user              #+#    #+#             */
/*   Updated: 2023/02/20 21:10:57 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	append_num(char **dst, unsigned int num)
{
	if (num == 0)
	{
		append_char(dst, '0');
		return ;
	}
	if (num / 10 != 0)
		append_num(dst, num / 10);
	append_char(dst, '0' + (num % 10));
}

void	expand_dolleeques(char **dst, char **rest, char *p)
{
	int	last_status;

	p = p + 2;
	last_status = 0;//本来はここに常に最終のステータスを保存する
	append_num(dst, last_status);
	*rest = p;
}