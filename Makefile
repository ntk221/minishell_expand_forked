NAME	=	minishell
SRCS	=	exec_func/exec_func.c tokenizer/tokenizer.c tokenizer/expand.c tokenizer/error.c\
			utils/split.c utils/putstr_fd.c utils/strlcat.c utils/strlcpy.c utils/strlen.c utils/strtrim.c utils/putchar_fd.c utils/strchr.c\
			utils/strdup.c\
			parser.c\
			readline/readline.c\
			map/map.c
OBJS	=	$(SRCS:%.c=%.o)
CC  	=	gcc
CFLAGS	=	-Wall -Werror -Wextra
RLDIR	=	$(shell brew --prefix readline)

all:$(NAME)

$(NAME):$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -Llibft -L$(RLDIR)/lib -I$(RLDIR)/include -o $(NAME) -lreadline -lft

debug:$(OBJS)
	$(CC) $(CFLAGS)  $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
