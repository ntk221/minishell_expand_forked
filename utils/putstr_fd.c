#include "../minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (s == NULL)
		return ;
	while ((*s) != '\0')
	{
		ft_putchar_fd((*s), fd);
		s = s + 1;
	}
}